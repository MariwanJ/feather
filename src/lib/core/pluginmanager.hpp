// =====================================================================================
// 
//       Filename:  pluginmanager.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/03/2014 03:22:04 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include "deps.hpp"
#include "types.hpp"
#include "command.hpp"
#include "parameter.hpp"

#define MAX_NODE_ID 900

namespace feather
{

    //struct PluginNodeFields{};

    struct PluginInfo {
        std::string path;
        void *handle;
        status (*do_it)(int,field::Fields&);
        void (*gl_draw)(FNode&,FGlInfo&);
        bool (*node_exist)(int); // is there a node with the given type and id in this plugin
        int (*node_type)(int);
        status(*create_fields)(int,field::Fields&); // creates a new instance of the nodes fields which will get deleted by the scenegraph when the node is removed.
        field::FieldBase* (*get_field)(int,int,field::Fields&);
        bool (*command_exist)(std::string cmd);
        status (*command)(std::string cmd, parameter::ParameterList);
    };

    struct test_call {
        test_call(int t) {};
        void operator()() {};
    };


    // DO_IT()

    template <int _Id>
    struct call_do_its {
        static status exec(int id, field::Fields& fields) { return call_do_its<_Id-1>::exec(id,fields); };
    };

    template <> struct call_do_its<0> { static status exec(int id, field::Fields& fields) { return status(FAILED,"could not find node"); }; };

    template <int _Id> status node_do_it(field::Fields& fields) { return status(FAILED,"no node found"); };
   
    struct call_do_it {
        call_do_it(int node,field::Fields& fields): m_node(node), m_fields(fields){};
        void operator()(PluginInfo n) { if(n.node_exist(m_node)) { std::cout << "found node " << m_node << std::endl; n.do_it(m_node,m_fields); } };
        private:
            int m_node;
            field::Fields& m_fields;
    };


    // GL DRAW 

    template <int _Id>
    struct call_gl_draws {
        static void exec(FNode& node, FGlInfo& info) { call_gl_draws<_Id-1>::exec(node,info); };
    };

    template <> struct call_gl_draws<0> { static void exec(FNode& node, FGlInfo& fields) {}; };
 
    template <int _Id> void node_gl_draw(FNode& node, FGlInfo& info) {};

    struct call_gl_draw {
        call_gl_draw(FNode& node, FGlInfo& info): m_node(node), m_info(info){};
        void operator()(PluginInfo n) { if(n.node_exist(m_node.node)) { std::cout << "found gl info for node " << m_node.uid << std::endl; n.gl_draw(m_node,m_info); } };

        private:
            FNode& m_node;
            FGlInfo& m_info;
    };


    // NODE MATCHING

    template <int _Id>
    struct find_nodes {
        static bool exec(int id) { return find_nodes<_Id-1>::exec(id); };
    };

    template <> struct find_nodes<0> { static bool exec(int id) { return false; }; };


    // NODE TYPE

    template <int _Id>
    struct find_node_type {
        static bool exec(int id) { return find_node_type<_Id-1>::exec(id); };
    };

    template <> struct find_node_type<0> { static bool exec(int id) { return false; }; };



    // GET FIELD DATA

    template <int _NodeId, int _FieldId>
    field::FieldBase* field_data(field::Fields& fields) { return NULL; };  

    // remember that the StartFieldId has to be the last field id + 1
    template <int _NodeId, int _StartFieldId>
    struct find_field {
        static field::FieldBase* exec(int fid, field::Fields& fields) {
            return find_field<_NodeId,_StartFieldId-1>::exec(fid,fields);
        };
    };

    template <int _NodeId>
    struct find_field<_NodeId,0> {
        static field::FieldBase* exec(int fid, field::Fields& fields) {
            return NULL;
        };
    };

    template <int _EndNode, int _StartNode, int _StartField>
        struct find_node_field {
            static field::FieldBase* exec(int nid, int fid, field::Fields& fields) {
                if(nid==_StartNode) {
                    return find_field<_StartNode,_StartField>::exec(fid,fields);
                }
                else
                    return find_node_field<_EndNode,_StartNode-1,_StartField>::exec(nid,fid,fields);
            };
        };

    template <int _StartNode, int _StartField>
        struct find_node_field<_StartNode,_StartNode,_StartField> {
            static field::FieldBase* exec(int nid, int fid, field::Fields& fields) {
                if(nid==_StartNode)
                    return find_field<_StartNode,_StartField>::exec(fid,fields);
                else 
                    return NULL;
            }; 
        };


    // CREATE FIELDS

    // Add Field is used to setup the Fields vector

    template <int _Node, int _StartKey>
    struct add_fields {
        static status exec(field::Fields& fields) {
            return add_fields<_Node,_StartKey-1>::exec(fields);
        };
    };

    template <int _Node> struct add_fields<_Node,0> { static status exec(field::Fields& fields) { return status(); }; };

    // Create Fields is used to get the field into the sg node container

    template <int _Id>
    struct find_create_fields {
        static  status exec(int id, field::Fields& fields) { return find_create_fields<_Id-1>::exec(id,fields); };
    };

    template <> struct find_create_fields<0> { static status exec(int id, field::Fields& fields) { return status(FAILED,"No matching node fould to create fields in"); }; };


    // COMMANDS 

    struct call_command {
        call_command(std::string cmd, parameter::ParameterList params){ m_cmd = cmd; m_params = params; };
        void operator()(PluginInfo n) { if(n.command_exist(m_cmd)) { std::cout << "found command " << m_cmd << std::endl; n.command(m_cmd,m_params); } };
        private:
            std::string m_cmd;
            parameter::ParameterList m_params;
    };
    


    // PLUGIN MANAGER

    class PluginManager
    {
        public:
            PluginManager();
            ~PluginManager();
            status load_plugins();
            status do_it(int node,field::Fields& fields); // this is called by the scenegraph
            void gl_draw(FNode& node, FGlInfo& info); 
            status create_fields(int node, field::Fields& fields); // this will return a new instance of the node's fields 
            field::FieldBase* get_fieldBase(int uid, int node, int field, field::Fields& fields);
            status run_command(std::string cmd, parameter::ParameterList);
            int min_uid();
            int max_uid();

        private:
            status load_node(PluginInfo &node);
            status load_command(PluginInfo &command);
            std::string m_pluginPath;
            std::vector<PluginInfo> m_plugins;
    };

} // namespace feather

#define C_PLUGIN_WRAPPER()\
    feather::status do_it(int, feather::field::Fields&);\
    void gl_draw(feather::FNode& node, feather::FGlInfo& info);\
    bool node_exist(int);\
    int node_type(int);\
    feather::status create_fields(int, feather::field::Fields&);\
    feather::field::FieldBase* get_field(int,int,feather::field::Fields&);\
    bool command_exist(std::string cmd);\
    feather::status command(std::string cmd, feather::parameter::ParameterList);\

#define PLUGIN_INIT(startnode,endnode)\
    /* call node do_it()'s */\
    feather::status do_it(int id, feather::field::Fields& fields) {\
        return call_do_its<MAX_NODE_ID>::exec(id,fields);\
    };\
    \
    /* get the node's gl info */\
    void gl_draw(feather::FNode& node, feather::FGlInfo& info) {\
        std::cout << "gl_draw\n";\
        call_gl_draws<MAX_NODE_ID>::exec(node,info);\
    };\
    \
    /* see if the node is in the plugin */\
    bool node_exist(int id) {\
        return find_nodes<MAX_NODE_ID>::exec(id);\
    };\
    \
    /* get the node type */\
    int node_type(int id) {\
        return find_node_type<MAX_NODE_ID>::exec(id);\
    };\
    \
    /* create a node field */\
    feather::status create_fields(int id,feather::field::Fields& fields) {\
        return find_create_fields<MAX_NODE_ID>::exec(id,fields);\
    };\
    \
    /* find the node's field */\
    feather::field::FieldBase* get_field(int nid, int fid, field::Fields& fields) {\
        return find_node_field<startnode,endnode,5>::exec(nid,fid,fields);\
    };


#endif

/***********************************************************************
 *
 * Filename: commands.hpp
 *
 * Description: Used to give qml access to the core.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "status.hpp"
#include "command.hpp"
#include "pluginmanager.hpp"
#include "field.hpp"
#include "draw.hpp"

namespace feather
{

    namespace qml
    {

        namespace command
        {

            FEATHER_API status init();

            // Node

            FEATHER_API unsigned int add_node(const unsigned int node, const std::string name); 
            FEATHER_API bool nodes_added(std::vector<unsigned int>& uids);
            FEATHER_API void remove_node(const unsigned int uid, status& error);
            FEATHER_API void nodes_updated();
            FEATHER_API bool node_exists(int uid);
            FEATHER_API status connect_nodes(int n1, int f1, int n2, int f2); 
            FEATHER_API void get_node_icon(const unsigned int nid, std::string& file, status& error);
            FEATHER_API void get_node_by_name(std::string name, unsigned int& uid);
            FEATHER_API void get_node_by_type(node::Type type, std::vector<unsigned int>& uids);
            FEATHER_API unsigned int get_node_id(const unsigned int uid, status& error);
            FEATHER_API status get_node_connected_uids(unsigned int uid, std::vector<unsigned int>& uids);
            FEATHER_API status get_node_connected_uids(unsigned int uid, unsigned int fid, std::vector<unsigned int>& uids);
            FEATHER_API status get_node_draw_items(int nid, draw::DrawItems& items);
            FEATHER_API status load_plugins();
            FEATHER_API status run_command(std::string cmd, feather::parameter::ParameterList params);
            FEATHER_API status run_command_string(std::string str);

            
            // Layer
            FEATHER_API status add_layer(FLayer layer);
            FEATHER_API status remove_layer(int lid);
            FEATHER_API status move_layer(int sid, int tid);
            FEATHER_API status get_layer(int id, FLayer &layer);
            FEATHER_API void set_layer_name(std::string name, int lid);
            FEATHER_API void set_layer_color(int r, int g, int b, int lid);
            FEATHER_API void set_layer_visible(bool v, int lid);
            FEATHER_API void set_layer_locked(bool l, int lid);
            FEATHER_API int layer_count();
            FEATHER_API void add_node_to_layer(int uid, int lid);


            // Fields
 
            // get field base 
            /*!
             * Returns a node's field that holds the value for the fid.
             * NOTE! if the field is connected it will return the field of the parent that's connected to it.
             * If you want to get the base of the node's fid, even if it's connected, use get_node_fieldBase().
             */
            FEATHER_API status get_field_base(unsigned int uid, unsigned int fid, feather::field::FieldBase* &f, unsigned int conn=0);
            FEATHER_API status get_field_base_array(unsigned int uid, unsigned int fid, std::vector<feather::field::FieldBase*> &f);
            /*!
             * Same as get_fieldBase() except it will return the base of the node field even if it's connected 
             */
            FEATHER_API status get_node_field_base(unsigned int uid, unsigned int fid, feather::field::FieldBase* &f);

            FEATHER_API status get_field_type(unsigned int uid, unsigned int nid, unsigned int fid, int& val);
 
            // get the field value
            FEATHER_API status get_field_val(unsigned int uid, unsigned int nid, unsigned int fid, bool& val, unsigned int conn=0);
            FEATHER_API status get_field_val(unsigned int uid, unsigned int nid, unsigned int fid, int& val, unsigned int conn=0);
            FEATHER_API status get_field_val(unsigned int uid, unsigned int nid, unsigned int fid, FReal& val, unsigned int conn=0);
            FEATHER_API status get_field_val(unsigned int uid, unsigned int nid, unsigned int fid, FMesh& val, unsigned int conn=0);
            // set the field value
            FEATHER_API status set_field_val(unsigned int uid, unsigned int nid, unsigned int fid, bool& val);
            FEATHER_API status set_field_val(unsigned int uid, unsigned int nid, unsigned int fid, int& val);
            FEATHER_API status set_field_val(unsigned int uid, unsigned int nid, unsigned int fid, FReal& val);
            FEATHER_API status set_field_val(unsigned int uid, unsigned int nid, unsigned int fid, FRealArray& val);
            FEATHER_API status set_field_val(unsigned int uid, unsigned int nid, unsigned int fid, FKeyArray& val);

            FEATHER_API status get_field_connection_status(int uid, int field, bool& val);
            FEATHER_API status get_field_connection_status(int uid, int node, int field, bool& val);
            FEATHER_API status get_field_connection_status(int suid, int sfid, int tuid, int tfid, bool& val);
            FEATHER_API status get_connected_fid(unsigned int uid, unsigned int fid, unsigned int& suid, unsigned int& sfid, unsigned int conn=0); // uid and fid are from the node's input
            FEATHER_API status get_fid_list(int uid, int nid, field::connection::Type conn, std::vector<field::FieldBase*>& list);
            FEATHER_API int get_field_count(int uid);
            FEATHER_API int get_in_field_count(int uid);
            FEATHER_API int get_out_field_count(int uid);
            FEATHER_API field::connection::Type get_field_connection_type(int uid, int fid);

            // SG EDITOR
            FEATHER_API void clear();
            FEATHER_API void get_node_out_connections(const unsigned int uid, std::vector<unsigned int>& uids);
            FEATHER_API int get_node_connection_count(int uid);
            FEATHER_API void get_node_name(const unsigned int uid, std::string& name, status& error);
            FEATHER_API void scenegraph_update();
            FEATHER_API int get_min_uid();
            FEATHER_API int get_max_uid();
            FEATHER_API void get_plugins(std::vector<PluginInfo>& list);

            // SG SELECTION
            FEATHER_API int selected_node();
            FEATHER_API status select_node(int uid);

            /* 
            status select_node(int type, int uid);
            status select_node(int type, int uid, int nid);
            status select_node(int type, int uid, int nid, int fid);
            */

            FEATHER_API status get_selected_nodes(std::vector<unsigned int>& uids);
            FEATHER_API void clear_selection();
   
        } // namespace command

    } // namespace qml

} // namespace feather

#endif

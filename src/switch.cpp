/*
 * libfreelan - A C++ library to establish peer-to-peer virtual private
 * networks.
 * Copyright (C) 2010-2011 Julien KAUFFMANN <julien.kauffmann@freelan.org>
 *
 * This file is part of libfreelan.
 *
 * libfreelan is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libfreelan is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 * If you intend to use libfreelan in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file switch.cpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief A switch class.
 */

#include "switch.hpp"

#include <asiotap/osi/ethernet_helper.hpp>

namespace freelan
{
	void switch_::receive_data(port_iterator_type it, boost::asio::const_buffer data)
	{
		switch (m_routing_method)
		{
			case configuration::RM_HUB:
				{
					send_data_from(it, data);

					break;
				}
			case configuration::RM_SWITCH:
				{
					asiotap::osi::const_helper<asiotap::osi::ethernet_frame> ethernet_helper(data);

					//TODO: Do something with ethernet_helper.target() and ethernet_helper.sender().
				}
		}
	}
	
	void switch_::send_data_from(port_iterator_type it, boost::asio::const_buffer data)
	{
		for (port_iterator_type port = m_ports.begin(); port != m_ports.end(); ++port)
		{
			if (port != it)
			{
				send_data_to(port, data);
			}
		}
	}
	
	void switch_::send_data_to(port_iterator_type it, boost::asio::const_buffer data)
	{
		it->write(data);
	}
}

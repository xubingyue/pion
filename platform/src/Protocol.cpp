// ------------------------------------------------------------------------
// Pion is a development platform for building Reactors that process Events
// ------------------------------------------------------------------------
// Copyright (C) 2007-2008 Atomic Labs, Inc.  (http://www.atomiclabs.com)
//
// Pion is free software: you can redistribute it and/or modify it under the
// terms of the GNU Affero General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// Pion is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for
// more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Pion.  If not, see <http://www.gnu.org/licenses/>.
//

#include <pion/platform/Protocol.hpp>
#include <pion/platform/ConfigManager.hpp>


namespace pion {		// begin namespace pion
namespace platform {	// begin namespace platform (Pion Platform Library)


// static members of Protocol
const std::string			Protocol::EVENT_ELEMENT_NAME = "EventType";
	
		
// Protocol member functions

bool Protocol::checkRecoveryPacket(bool request, const char* ptr, size_t len)
{
	return false;
}

void Protocol::setConfig(const Vocabulary& v, const xmlNodePtr config_ptr)
{
	PlatformPlugin::setConfig(v, config_ptr);
	
	// determine the type of event used by the protocol
	std::string protocol_event_str;
	if (! ConfigManager::getConfigOption(EVENT_ELEMENT_NAME, protocol_event_str,
										 config_ptr))
		throw EmptyEventException(getId());

	// find the Term reference number for the event type
	m_event_type = v.findTerm(protocol_event_str);
	if (m_event_type == Vocabulary::UNDEFINED_TERM_REF)
		throw UnknownTermException(protocol_event_str);

	// make sure that it is an object type Term
	if (v[m_event_type].term_type != Vocabulary::TYPE_OBJECT)
		throw NotAnObjectException(protocol_event_str);
}
	
void Protocol::updateVocabulary(const Vocabulary& v)
{
	PlatformPlugin::updateVocabulary(v);

	// assume that term references never change
}

}	// end namespace platform
}	// end namespace pion

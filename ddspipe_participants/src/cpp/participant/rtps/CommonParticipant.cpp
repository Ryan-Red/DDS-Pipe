// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <memory>

#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/TCPv6TransportDescriptor.h>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/UDPv6TransportDescriptor.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/RTPSDomain.h>

#include <cpp_utils/exception/InitializationException.hpp>
#include <cpp_utils/Log.hpp>
#include <cpp_utils/utils.hpp>

#include <ddspipe_core/types/data/RpcPayloadData.hpp>
#include <ddspipe_core/types/data/RtpsPayloadData.hpp>
#include <ddspipe_core/types/dds/DomainId.hpp>
#include <ddspipe_core/types/topic/rpc/RpcTopic.hpp>

#include <ddspipe_participants/library/library_dll.h>
#include <ddspipe_participants/participant/rtps/CommonParticipant.hpp>
#include <ddspipe_participants/reader/auxiliar/BlankReader.hpp>
#include <ddspipe_participants/reader/rpc/SimpleReader.hpp>
#include <ddspipe_participants/reader/rtps/SimpleReader.hpp>
#include <ddspipe_participants/reader/rtps/SpecificQoSReader.hpp>
#include <ddspipe_participants/writer/auxiliar/BlankWriter.hpp>
#include <ddspipe_participants/writer/rpc/SimpleWriter.hpp>
#include <ddspipe_participants/writer/rtps/MultiWriter.hpp>
#include <ddspipe_participants/writer/rtps/QoSSpecificWriter.hpp>
#include <ddspipe_participants/writer/rtps/SimpleWriter.hpp>
#include <ddspipe_participants/writer/dds/SimpleWriter.hpp>
#include <utils/utils.hpp>

namespace eprosima {
namespace ddspipe {
namespace participants {
namespace rtps {

CommonParticipant::CommonParticipant(
        const std::shared_ptr<ParticipantConfiguration>& participant_configuration,
        const std::shared_ptr<core::PayloadPool>& payload_pool,
        const std::shared_ptr<core::DiscoveryDatabase>& discovery_database,
        const core::types::DomainId& domain_id,
        const fastrtps::rtps::RTPSParticipantAttributes& participant_attributes)
    : configuration_(participant_configuration)
    , payload_pool_(payload_pool)
    , discovery_database_(discovery_database)
    , domain_id_(domain_id)
    , participant_attributes_(participant_attributes)
{
    // Do nothing
}

CommonParticipant::~CommonParticipant()
{
    if (rtps_participant_)
    {
        fastrtps::rtps::RTPSDomain::removeRTPSParticipant(rtps_participant_);
    }
}

void CommonParticipant::init()
{
    create_participant_(
        domain_id_,
        participant_attributes_);
}

void CommonParticipant::onParticipantDiscovery(
        fastrtps::rtps::RTPSParticipant* participant,
        fastrtps::rtps::ParticipantDiscoveryInfo&& info)
{
    if (info.info.m_guid.guidPrefix != participant->getGuid().guidPrefix)
    {
        if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::DISCOVERED_PARTICIPANT)
        {
            logInfo(DDSPIPE_DISCOVERY,
                    "Found in Participant " << configuration_->id << " new Participant " << info.info.m_guid << ".");
        }
        else if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::CHANGED_QOS_PARTICIPANT)
        {
            logInfo(DDSPIPE_DISCOVERY, "Participant " << info.info.m_guid << " changed QoS.");
        }
        else if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::REMOVED_PARTICIPANT)
        {
            logInfo(DDSPIPE_DISCOVERY, "Participant " << info.info.m_guid << " removed.");
        }
        else if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::DROPPED_PARTICIPANT)
        {
            logInfo(DDSPIPE_DISCOVERY, "Participant " << info.info.m_guid << " dropped.");
        }
        else if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::IGNORED_PARTICIPANT)
        {
            logInfo(DDSPIPE_DISCOVERY, "Participant " << info.info.m_guid << " ignored.");
        }
    }
}

void CommonParticipant::onReaderDiscovery(
        fastrtps::rtps::RTPSParticipant* participant,
        fastrtps::rtps::ReaderDiscoveryInfo&& info)
{
    if (info.info.guid().guidPrefix != participant->getGuid().guidPrefix)
    {
        core::types::Endpoint info_reader = detail::create_endpoint_from_info_<fastrtps::rtps::ReaderDiscoveryInfo>(
            info, this->id());

        if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::DISCOVERED_READER)
        {
            logInfo(DDSPIPE_DISCOVERY,
                    "Found in Participant " << configuration_->id << " new Reader " << info.info.guid() << ".");

            this->discovery_database_->add_endpoint(info_reader);
        }
        else if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::CHANGED_QOS_READER)
        {
            logInfo(DDSPIPE_DISCOVERY, "Reader " << info.info.guid() << " changed TopicQoS.");

            this->discovery_database_->update_endpoint(info_reader);
        }
        else if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::REMOVED_READER)
        {
            logInfo(DDSPIPE_DISCOVERY, "Reader " << info.info.guid() << " removed.");

            info_reader.active = false;
            this->discovery_database_->update_endpoint(info_reader);
        }
        else if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::IGNORED_READER)
        {
            logInfo(DDSPIPE_DISCOVERY, "Reader " << info.info.guid() << " ignored.");

            // Do not notify discovery database (design choice that might be changed in the future)
        }
    }
}

void CommonParticipant::onWriterDiscovery(
        fastrtps::rtps::RTPSParticipant* participant,
        fastrtps::rtps::WriterDiscoveryInfo&& info)
{
    if (info.info.guid().guidPrefix != participant->getGuid().guidPrefix)
    {
        core::types::Endpoint info_writer = detail::create_endpoint_from_info_<fastrtps::rtps::WriterDiscoveryInfo>(
            info, this->id());

        if (info.status == fastrtps::rtps::WriterDiscoveryInfo::DISCOVERED_WRITER)
        {
            logInfo(DDSPIPE_DISCOVERY,
                    "Found in Participant " << configuration_->id << " new Writer " << info.info.guid() << ".");

            this->discovery_database_->add_endpoint(info_writer);
        }
        else if (info.status == fastrtps::rtps::WriterDiscoveryInfo::CHANGED_QOS_WRITER)
        {
            logInfo(DDSPIPE_DISCOVERY, "Writer " << info.info.guid() << " changed TopicQoS.");

            this->discovery_database_->update_endpoint(info_writer);
        }
        else if (info.status == fastrtps::rtps::WriterDiscoveryInfo::REMOVED_WRITER)
        {
            logInfo(DDSPIPE_DISCOVERY, "Writer " << info.info.guid() << " removed.");

            info_writer.active = false;
            this->discovery_database_->update_endpoint(info_writer);
        }
        else if (info.status == fastrtps::rtps::WriterDiscoveryInfo::IGNORED_WRITER)
        {
            logInfo(DDSPIPE_DISCOVERY, "Writer " << info.info.guid() << " ignored.");

            // Do not notify discovery database (design choice that might be changed in the future)
        }
    }
}

core::types::Endpoint CommonParticipant::simulate_endpoint(
        const core::types::DdsTopic& topic,
        const core::types::ParticipantId& discoverer_id)
{
    core::types::Endpoint endpoint;
    endpoint.kind = core::types::EndpointKind::reader;
    endpoint.guid = core::types::Guid::new_unique_guid();
    endpoint.topic = topic;
    endpoint.discoverer_participant_id = discoverer_id;
    endpoint.topic.m_topic_discoverer = discoverer_id;

    return endpoint;
}

template<>
DDSPIPE_PARTICIPANTS_DllAPI
std::shared_ptr<eprosima::fastdds::rtps::UDPv4TransportDescriptor>
CommonParticipant::create_descriptor(
        std::set<types::IpType> whitelist)
{
    std::shared_ptr<eprosima::fastdds::rtps::UDPv4TransportDescriptor> udp_transport =
            std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();

    for (const types::IpType& ip : whitelist)
    {
        if (types::Address::is_ipv4_correct(ip))
        {
            udp_transport->interfaceWhiteList.emplace_back(ip);
            logInfo(DDSPIPE_COMMON_PARTICIPANT,
                    "Adding " << ip << " to UDP whitelist interfaces.");
        }
        else
        {
            // Invalid address, continue with next one
            logWarning(DDSPIPE_COMMON_PARTICIPANT,
                    "Not valid IPv4. Discarding UDP whitelist interface " << ip << ".");
        }
    }

    return udp_transport;
}

template<>
DDSPIPE_PARTICIPANTS_DllAPI
std::shared_ptr<eprosima::fastdds::rtps::UDPv6TransportDescriptor>
CommonParticipant::create_descriptor(
        std::set<types::IpType> whitelist)
{
    std::shared_ptr<eprosima::fastdds::rtps::UDPv6TransportDescriptor> udp_transport =
            std::make_shared<eprosima::fastdds::rtps::UDPv6TransportDescriptor>();

    for (const types::IpType& ip : whitelist)
    {
        if (types::Address::is_ipv6_correct(ip))
        {
            udp_transport->interfaceWhiteList.emplace_back(ip);
            logInfo(DDSPIPE_COMMON_PARTICIPANT,
                    "Adding " << ip << " to UDP whitelist interfaces.");
        }
        else
        {
            // Invalid address, continue with next one
            logWarning(DDSPIPE_COMMON_PARTICIPANT,
                    "Not valid IPv6. Discarding UDP whitelist interface " << ip << ".");
        }
    }

    return udp_transport;
}

template<>
DDSPIPE_PARTICIPANTS_DllAPI
std::shared_ptr<eprosima::fastdds::rtps::TCPv4TransportDescriptor>
CommonParticipant::create_descriptor(
        std::set<types::IpType> whitelist)
{
    std::shared_ptr<eprosima::fastdds::rtps::TCPv4TransportDescriptor> tcp_transport =
            std::make_shared<eprosima::fastdds::rtps::TCPv4TransportDescriptor>();

    for (const types::IpType& ip : whitelist)
    {
        if (types::Address::is_ipv4_correct(ip))
        {
            tcp_transport->interfaceWhiteList.emplace_back(ip);
            logInfo(DDSPIPE_COMMON_PARTICIPANT,
                    "Adding " << ip << " to TCP whitelist interfaces.");
        }
        else
        {
            // Invalid address, continue with next one
            logWarning(DDSPIPE_COMMON_PARTICIPANT,
                    "Not valid IPv4. Discarding TCP whitelist interface " << ip << ".");
        }
    }

    return tcp_transport;
}

template<>
DDSPIPE_PARTICIPANTS_DllAPI
std::shared_ptr<eprosima::fastdds::rtps::TCPv6TransportDescriptor>
CommonParticipant::create_descriptor(
        std::set<types::IpType> whitelist)
{
    std::shared_ptr<eprosima::fastdds::rtps::TCPv6TransportDescriptor> tcp_transport =
            std::make_shared<eprosima::fastdds::rtps::TCPv6TransportDescriptor>();

    for (const types::IpType& ip : whitelist)
    {
        if (types::Address::is_ipv6_correct(ip))
        {
            tcp_transport->interfaceWhiteList.emplace_back(ip);
            logInfo(DDSPIPE_COMMON_PARTICIPANT,
                    "Adding " << ip << " to TCP whitelist interfaces.");
        }
        else
        {
            // Invalid address, continue with next one
            logWarning(DDSPIPE_COMMON_PARTICIPANT,
                    "Not valid IPv6. Discarding TCP whitelist interface " << ip << ".");
        }
    }

    return tcp_transport;
}

bool CommonParticipant::is_repeater() const noexcept
{
    return configuration_->is_repeater;
}

core::types::ParticipantId CommonParticipant::id() const noexcept
{
    return configuration_->id;
}

bool CommonParticipant::is_rtps_kind() const noexcept
{
    return true;
}

core::types::TopicQoS CommonParticipant::topic_qos() const noexcept
{
    return configuration_->topic_qos;
}

void CommonParticipant::create_participant_(
        const core::types::DomainId& domain,
        const fastrtps::rtps::RTPSParticipantAttributes& participant_attributes)
{
    logInfo(DDSPIPE_RTPS_PARTICIPANT,
            "Creating Participant in domain " << domain);
        
    int domain_int = domain;

    eprosima::fastdds::dds::DomainParticipantQos participantQos;

    fastrtps::rtps::RTPSParticipantAttributes participant_att = participant_attributes;
    participant_att.builtin.discovery_config.discoveryProtocol = eprosima::fastrtps::rtps::DiscoveryProtocol_t::SUPER_CLIENT;
    participantQos.wire_protocol().builtin.discovery_config.discoveryProtocol = eprosima::fastrtps::rtps::DiscoveryProtocol_t::SUPER_CLIENT;
    

    participant_att.builtin.typelookup_config.use_client = true;

    YAML::Node config = YAML::LoadFile("/usr/include/dls2/util/messaging/servers.yaml");

    std::string server_ip = config[domain_int]["ip"].as<std::string>();
    double server_port = config[domain_int]["port"].as<double>();
    std::string server_guid_prefix = config[domain_int]["guid_prefix"].as<std::string>();

    // Define server locator
    eprosima::fastrtps::rtps::Locator_t server_locator;
    eprosima::fastrtps::rtps::IPLocator::setIPv4(server_locator, server_ip);
    eprosima::fastrtps::rtps::IPLocator::setPhysicalPort(server_locator, server_port);
    server_locator.kind = LOCATOR_KIND_UDPv4;

    eprosima::fastrtps::rtps::RemoteServerAttributes remote_server_attr;
    remote_server_attr.metatrafficUnicastLocatorList.push_back(server_locator);
    // -- Set the GUID prefix to identify the server
    remote_server_attr.ReadguidPrefix(server_guid_prefix.c_str());
    // -- Connect to the remote server
    participant_att.builtin.discovery_config.m_DiscoveryServers.push_back(remote_server_attr);
    participantQos.wire_protocol().builtin.discovery_config.m_DiscoveryServers.push_back(remote_server_attr);

    auto udp_transport = std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();
		
	participantQos.transport().user_transports.push_back(udp_transport);

    // Listener must be set in creation as no callbacks should be missed
    // It is safe to do so here as object is already created and callbacks do not require anything set in this method
    rtps_participant_ = fastrtps::rtps::RTPSDomain::createParticipant(
        domain_int,
        participant_att,
        this);

    if (!rtps_participant_)
    {
        throw utils::InitializationException(
                  utils::Formatter() << "Error creating RTPS Participant " << this->id());
    }
    eprosima::fastdds::dds::StatusMask mask;

    dds_participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(
        domain, 
        participantQos,
        &dds_listener,
        mask.none()
    );


    logInfo(DDSPIPE_RTPS_PARTICIPANT,
            "New Participant created with id " << this->id() <<
            " in domain " << domain << " with guid " << rtps_participant_->getGuid() <<
            (this->is_repeater() ? " (repeater)" : " (non repeater)"));
}

std::shared_ptr<core::IWriter> CommonParticipant::create_writer(
        const core::ITopic& topic)
{
    std::cout << "creating the writer rn" << std::endl;
    // Can only create DDS Topics
    const core::types::DdsTopic* dds_topic_ptr = dynamic_cast<const core::types::DdsTopic*>(&topic);
    if (!dds_topic_ptr)
    {
        logDebug(DDSPIPE_RTPS_PARTICIPANT, "Not creating Writer for topic " << topic.topic_name());
        return std::make_shared<BlankWriter>();
    }

    const core::types::DdsTopic& dds_topic = *dds_topic_ptr;


    std::cout << "Creating a Writer for Topic: " << dds_topic_ptr->topic_name() << std::endl;;
    


    if (topic.internal_type_discriminator() == core::types::INTERNAL_TOPIC_TYPE_RPC)
    {
        logDebug(DDSPIPE_RTPS_PARTICIPANT,
                "Creating RPC Writer for topic " << topic.topic_name());
        auto writer = std::make_shared<rpc::SimpleWriter>(
            this->id(),
            dds_topic,
            this->payload_pool_,
            rtps_participant_,
            this->configuration_->is_repeater);
        writer->init();

        return writer;
    }
    else if (topic.internal_type_discriminator() == core::types::INTERNAL_TOPIC_TYPE_RTPS)
    {
        std::cout << "rtps internal type" << std::endl;
        if (dds_topic.topic_qos.has_partitions() || dds_topic.topic_qos.has_ownership())
        {
            std::cout << "has partitions or has ownership" << std::endl;
            // Notice that MultiWriter does not require an init call
            return std::make_shared<MultiWriter>(
                this->id(),
                dds_topic,
                this->payload_pool_,
                rtps_participant_,
                this->configuration_->is_repeater);
        }
        else
        {
            std::cout << "old fashioned way B)" << std::endl;


            auto type_object = eprosima::fastrtps::types::TypeObjectFactory::get_instance()->get_type_object(dds_topic_ptr->type_name, true);



            auto type_id =
                    eprosima::fastrtps::types::TypeObjectFactory::get_instance()->get_type_identifier(dds_topic_ptr->type_name,
                            true);


            auto dyn_type = eprosima::fastrtps::types::TypeObjectFactory::get_instance()->build_dynamic_type(dds_topic_ptr->type_name,
                            type_id,
                            type_object);


            eprosima::fastdds::dds::TypeSupport ts( new eprosima::fastrtps::types::DynamicPubSubType(dyn_type));
            ts->setName("blind_state");

            ts->auto_fill_type_information(false);
            ts->auto_fill_type_object(true);
            ts.register_type(dds_participant);


            // dds_participant->register_type(ts);
            auto dds_topic_info = dds_participant->create_topic(
                dds_topic_ptr->topic_name(),
                dds_topic_ptr->type_name, 
                eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
            std::cout <<  dds_topic_ptr->type_name << std::endl;
            std::cout <<  dds_topic_ptr->topic_name() << std::endl;


            std::cout << "created this kind of writer" << std::endl;
            auto writer = std::make_shared<eprosima::ddspipe::participants::dds::SimpleWriter>(
                this->id(),
                dds_topic,
                this->payload_pool_,
                dds_participant,
                dds_topic_info);
            writer->init();

            return writer;
        }
    }
    else
    {
        logDevError(DDSPIPE_RTPS_PARTICIPANT, "Incorrect dds Topic in Writer creation.");
        std::cout << "Incorrect dds Topic in Writer creation." << std::endl;
        return std::make_shared<BlankWriter>();
    }
}

std::shared_ptr<core::IReader> CommonParticipant::create_reader(
        const core::ITopic& topic)
{
    // Can only create DDS Topics
    const core::types::DdsTopic* dds_topic_ptr = dynamic_cast<const core::types::DdsTopic*>(&topic);

    if (!dds_topic_ptr)
    {
        logDebug(DDSPIPE_RTPS_PARTICIPANT, "Not creating Reader for topic " << topic.topic_name());
        return std::make_shared<BlankReader>();
    }

    const core::types::DdsTopic& dds_topic = *dds_topic_ptr;

    std::cout << "Creating Readers for Topic: " << dds_topic_ptr->topic_name() << std::endl;;

    if (topic.internal_type_discriminator() == core::types::INTERNAL_TOPIC_TYPE_RPC)
    {
        logDebug(DDSPIPE_RTPS_PARTICIPANT,
                "Creating RPC Reader for topic " << topic.topic_name());

        auto reader = std::make_shared<rpc::SimpleReader>(
            this->id(),
            dds_topic,
            this->payload_pool_,
            rtps_participant_);
        reader->init();

        return reader;
    }
    else if (topic.internal_type_discriminator() == core::types::INTERNAL_TOPIC_TYPE_RTPS)
    {
        if (dds_topic.topic_qos.has_partitions() || dds_topic.topic_qos.has_ownership())
        {
            auto reader = std::make_shared<SpecificQoSReader>(
                this->id(),
                dds_topic,
                this->payload_pool_,
                rtps_participant_,
                discovery_database_);
            reader->init();

            return reader;
        }
        else
        {
            auto reader = std::make_shared<SimpleReader>(
                this->id(),
                dds_topic,
                this->payload_pool_,
                rtps_participant_);
            reader->init();

            return reader;
        }
    }
    else
    {
        logDevError(DDSPIPE_RTPS_PARTICIPANT, "Incorrect dds Topic in Reader creation.");
        return std::make_shared<BlankReader>();
    }
}

fastrtps::rtps::RTPSParticipantAttributes
CommonParticipant::reckon_participant_attributes_(
        const ParticipantConfiguration* participant_configuration)
{
    fastrtps::rtps::RTPSParticipantAttributes params;

    // params.builtin.discovery_config.discoveryProtocol = eprosima::fastrtps::rtps::DiscoveryProtocol_t::SUPER_CLIENT;
    
    // Add Participant name
    params.setName(participant_configuration->id.c_str());

    // Ignore the local endpoints so that the reader and writer of the same participant don't match.
    params.properties.properties().emplace_back(
        "fastdds.ignore_local_endpoints",
        "true");

    // Set app properties
    params.properties.properties().emplace_back(
        "fastdds.application.id",
        participant_configuration->app_id,
        "true");
    params.properties.properties().emplace_back(
        "fastdds.application.metadata",
        participant_configuration->app_metadata,
        "true");

    return params;
}

} /* namespace rtps */
} /* namespace participants */
} /* namespace ddspipe */
} /* namespace eprosima */

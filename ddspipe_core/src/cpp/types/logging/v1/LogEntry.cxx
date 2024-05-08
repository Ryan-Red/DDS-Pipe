// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/*!
 * @file LogEntry.cpp
 * This source file contains the implementation of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include <ddspipe_core/types/logging/v1/LogEntry.h>

#include <ddspipe_core/types/logging/v1/LogEntryTypeObject.h>

#include <fastcdr/Cdr.h>


#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

namespace helper {
namespace internal {

enum class Size
{
    UInt8,
    UInt16,
    UInt32,
    UInt64,
};

constexpr Size get_size(
        int s)
{
    return (s <= 8 ) ? Size::UInt8:
           (s <= 16) ? Size::UInt16:
           (s <= 32) ? Size::UInt32: Size::UInt64;
}

template<Size s>
struct FindTypeH;

template<>
struct FindTypeH<Size::UInt8>
{
    using type = std::uint8_t;
};

template<>
struct FindTypeH<Size::UInt16>
{
    using type = std::uint16_t;
};

template<>
struct FindTypeH<Size::UInt32>
{
    using type = std::uint32_t;
};

template<>
struct FindTypeH<Size::UInt64>
{
    using type = std::uint64_t;
};
} // namespace internal

template<int S>
struct FindType
{
    using type = typename internal::FindTypeH<internal::get_size(S)>::type;
};
} // namespace helper

#define LogEntry_max_cdr_typesize 792ULL;




LogEntry::LogEntry()
{
    // long m_event
    m_event = 0;
    // Kind m_kind
    m_kind = ::Info;
    // /type_d() m_category

    // /type_d() m_message

    // /type_d() m_timestamp


    // Just to register all known types
    registerLogEntryTypes();
}

LogEntry::~LogEntry()
{
}

LogEntry::LogEntry(
        const LogEntry& x)
{
    m_event = x.m_event;


    m_kind = x.m_kind;


    m_category = x.m_category;


    m_message = x.m_message;


    m_timestamp = x.m_timestamp;

}

LogEntry::LogEntry(
        LogEntry&& x) noexcept
{
    m_event = x.m_event;


    m_kind = x.m_kind;


    m_category = std::move(x.m_category);


    m_message = std::move(x.m_message);


    m_timestamp = std::move(x.m_timestamp);

}

LogEntry& LogEntry::operator =(
        const LogEntry& x)
{
    m_event = x.m_event;


    m_kind = x.m_kind;


    m_category = x.m_category;


    m_message = x.m_message;


    m_timestamp = x.m_timestamp;

    return *this;
}

LogEntry& LogEntry::operator =(
        LogEntry&& x) noexcept
{
    m_event = x.m_event;


    m_kind = x.m_kind;


    m_category = std::move(x.m_category);


    m_message = std::move(x.m_message);


    m_timestamp = std::move(x.m_timestamp);

    return *this;
}

bool LogEntry::operator ==(
        const LogEntry& x) const
{
    return (m_event == x.m_event &&
           m_kind == x.m_kind &&
           m_category == x.m_category &&
           m_message == x.m_message &&
           m_timestamp == x.m_timestamp);
}

bool LogEntry::operator !=(
        const LogEntry& x) const
{
    return !(*this == x);
}

size_t LogEntry::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return LogEntry_max_cdr_typesize;
}

size_t LogEntry::getCdrSerializedSize(
        const LogEntry& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.category().size() + 1;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.message().size() + 1;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.timestamp().size() + 1;


    return current_alignment - initial_alignment;
}

void LogEntry::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{
    scdr << m_event;

    scdr << (uint32_t)m_kind;

    scdr << m_category.c_str();

    scdr << m_message.c_str();

    scdr << m_timestamp.c_str();

}

void LogEntry::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{
    dcdr >> m_event;



    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_kind = (Kind)enum_value;
    }



    dcdr >> m_category;



    dcdr >> m_message;



    dcdr >> m_timestamp;


}

bool LogEntry::isKeyDefined()
{
    return true;
}

void LogEntry::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;

    scdr << m_event;





}

/*!
 * @brief This function sets a value in member event
 * @param _event New value for member event
 */
void LogEntry::event(
        int32_t _event)
{
    m_event = _event;
}

/*!
 * @brief This function returns the value of member event
 * @return Value of member event
 */
int32_t LogEntry::event() const
{
    return m_event;
}

/*!
 * @brief This function returns a reference to member event
 * @return Reference to member event
 */
int32_t& LogEntry::event()
{
    return m_event;
}

/*!
 * @brief This function sets a value in member kind
 * @param _kind New value for member kind
 */
void LogEntry::kind(
        Kind _kind)
{
    m_kind = _kind;
}

/*!
 * @brief This function returns the value of member kind
 * @return Value of member kind
 */
Kind LogEntry::kind() const
{
    return m_kind;
}

/*!
 * @brief This function returns a reference to member kind
 * @return Reference to member kind
 */
Kind& LogEntry::kind()
{
    return m_kind;
}

/*!
 * @brief This function copies the value in member category
 * @param _category New value to be copied in member category
 */
void LogEntry::category(
        const std::string& _category)
{
    m_category = _category;
}

/*!
 * @brief This function moves the value in member category
 * @param _category New value to be moved in member category
 */
void LogEntry::category(
        std::string&& _category)
{
    m_category = std::move(_category);
}

/*!
 * @brief This function returns a constant reference to member category
 * @return Constant reference to member category
 */
const std::string& LogEntry::category() const
{
    return m_category;
}

/*!
 * @brief This function returns a reference to member category
 * @return Reference to member category
 */
std::string& LogEntry::category()
{
    return m_category;
}

/*!
 * @brief This function copies the value in member message
 * @param _message New value to be copied in member message
 */
void LogEntry::message(
        const std::string& _message)
{
    m_message = _message;
}

/*!
 * @brief This function moves the value in member message
 * @param _message New value to be moved in member message
 */
void LogEntry::message(
        std::string&& _message)
{
    m_message = std::move(_message);
}

/*!
 * @brief This function returns a constant reference to member message
 * @return Constant reference to member message
 */
const std::string& LogEntry::message() const
{
    return m_message;
}

/*!
 * @brief This function returns a reference to member message
 * @return Reference to member message
 */
std::string& LogEntry::message()
{
    return m_message;
}

/*!
 * @brief This function copies the value in member timestamp
 * @param _timestamp New value to be copied in member timestamp
 */
void LogEntry::timestamp(
        const std::string& _timestamp)
{
    m_timestamp = _timestamp;
}

/*!
 * @brief This function moves the value in member timestamp
 * @param _timestamp New value to be moved in member timestamp
 */
void LogEntry::timestamp(
        std::string&& _timestamp)
{
    m_timestamp = std::move(_timestamp);
}

/*!
 * @brief This function returns a constant reference to member timestamp
 * @return Constant reference to member timestamp
 */
const std::string& LogEntry::timestamp() const
{
    return m_timestamp;
}

/*!
 * @brief This function returns a reference to member timestamp
 * @return Reference to member timestamp
 */
std::string& LogEntry::timestamp()
{
    return m_timestamp;
}

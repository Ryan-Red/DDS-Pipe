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
 * @file char_sequence.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "char_sequence.h"
#include "char_sequenceTypeObject.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

char_sequence::char_sequence()
{
    // m_chars com.eprosima.idl.parser.typecode.SequenceTypeCode@3fd7a715


    // Just to register all known types
    registerchar_sequenceTypes();
}

char_sequence::~char_sequence()
{
}

char_sequence::char_sequence(
        const char_sequence& x)
{
    m_chars = x.m_chars;
}

char_sequence::char_sequence(
        char_sequence&& x) noexcept
{
    m_chars = std::move(x.m_chars);
}

char_sequence& char_sequence::operator =(
        const char_sequence& x)
{

    m_chars = x.m_chars;

    return *this;
}

char_sequence& char_sequence::operator =(
        char_sequence&& x) noexcept
{

    m_chars = std::move(x.m_chars);

    return *this;
}

bool char_sequence::operator ==(
        const char_sequence& x) const
{

    return (m_chars == x.m_chars);
}

bool char_sequence::operator !=(
        const char_sequence& x) const
{
    return !(*this == x);
}

size_t char_sequence::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (100 * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    return current_alignment - initial_alignment;
}

size_t char_sequence::getCdrSerializedSize(
        const char_sequence& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    if (data.chars().size() > 0)
    {
        current_alignment += (data.chars().size() * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);
    }



    return current_alignment - initial_alignment;
}

void char_sequence::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_chars;
}

void char_sequence::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_chars;}

/*!
 * @brief This function copies the value in member chars
 * @param _chars New value to be copied in member chars
 */
void char_sequence::chars(
        const std::vector<char>& _chars)
{
    m_chars = _chars;
}

/*!
 * @brief This function moves the value in member chars
 * @param _chars New value to be moved in member chars
 */
void char_sequence::chars(
        std::vector<char>&& _chars)
{
    m_chars = std::move(_chars);
}

/*!
 * @brief This function returns a constant reference to member chars
 * @return Constant reference to member chars
 */
const std::vector<char>& char_sequence::chars() const
{
    return m_chars;
}

/*!
 * @brief This function returns a reference to member chars
 * @return Reference to member chars
 */
std::vector<char>& char_sequence::chars()
{
    return m_chars;
}

size_t char_sequence::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t current_align = current_alignment;



    return current_align;
}

bool char_sequence::isKeyDefined()
{
    return false;
}

void char_sequence::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;

}
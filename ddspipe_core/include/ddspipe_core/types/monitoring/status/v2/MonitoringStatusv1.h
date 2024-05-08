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
 * @file MonitoringStatus.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#include <fastcdr/config.h>

#if FASTCDR_VERSION_MAJOR == 1

#ifndef _FAST_DDS_GENERATED_MONITORINGSTATUS_H_
#define _FAST_DDS_GENERATED_MONITORINGSTATUS_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(MONITORINGSTATUS_SOURCE)
#define MONITORINGSTATUS_DllAPI __declspec( dllexport )
#else
#define MONITORINGSTATUS_DllAPI __declspec( dllimport )
#endif // MONITORINGSTATUS_SOURCE
#else
#define MONITORINGSTATUS_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define MONITORINGSTATUS_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima





/*!
 * @brief This class represents the structure MonitoringErrorStatus defined by the user in the IDL file.
 * @ingroup MonitoringStatus
 */
class MonitoringErrorStatus
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport MonitoringErrorStatus();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~MonitoringErrorStatus();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object MonitoringErrorStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringErrorStatus(
            const MonitoringErrorStatus& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object MonitoringErrorStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringErrorStatus(
            MonitoringErrorStatus&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object MonitoringErrorStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringErrorStatus& operator =(
            const MonitoringErrorStatus& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object MonitoringErrorStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringErrorStatus& operator =(
            MonitoringErrorStatus&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x MonitoringErrorStatus object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const MonitoringErrorStatus& x) const;

    /*!
     * @brief Comparison operator.
     * @param x MonitoringErrorStatus object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const MonitoringErrorStatus& x) const;

    /*!
     * @brief This function sets a value in member type_mismatch
     * @param _type_mismatch New value for member type_mismatch
     */
    eProsima_user_DllExport void type_mismatch(
            bool _type_mismatch);

    /*!
     * @brief This function returns the value of member type_mismatch
     * @return Value of member type_mismatch
     */
    eProsima_user_DllExport bool type_mismatch() const;

    /*!
     * @brief This function returns a reference to member type_mismatch
     * @return Reference to member type_mismatch
     */
    eProsima_user_DllExport bool& type_mismatch();


    /*!
     * @brief This function sets a value in member qos_mismatch
     * @param _qos_mismatch New value for member qos_mismatch
     */
    eProsima_user_DllExport void qos_mismatch(
            bool _qos_mismatch);

    /*!
     * @brief This function returns the value of member qos_mismatch
     * @return Value of member qos_mismatch
     */
    eProsima_user_DllExport bool qos_mismatch() const;

    /*!
     * @brief This function returns a reference to member qos_mismatch
     * @return Reference to member qos_mismatch
     */
    eProsima_user_DllExport bool& qos_mismatch();


    /*!
     * @brief This function returns the maximum serialized size of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(
            const MonitoringErrorStatus& data,
            size_t current_alignment = 0);



    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(
            eprosima::fastcdr::Cdr& cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(
            eprosima::fastcdr::Cdr& cdr);




    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(
            eprosima::fastcdr::Cdr& cdr) const;

private:

    bool m_type_mismatch;
    bool m_qos_mismatch;

};



/*!
 * @brief This class represents the structure MonitoringStatus defined by the user in the IDL file.
 * @ingroup MonitoringStatus
 */
class MonitoringStatus
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport MonitoringStatus();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~MonitoringStatus();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object MonitoringStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringStatus(
            const MonitoringStatus& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object MonitoringStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringStatus(
            MonitoringStatus&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object MonitoringStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringStatus& operator =(
            const MonitoringStatus& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object MonitoringStatus that will be copied.
     */
    eProsima_user_DllExport MonitoringStatus& operator =(
            MonitoringStatus&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x MonitoringStatus object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const MonitoringStatus& x) const;

    /*!
     * @brief Comparison operator.
     * @param x MonitoringStatus object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const MonitoringStatus& x) const;

    /*!
     * @brief This function copies the value in member error_status
     * @param _error_status New value to be copied in member error_status
     */
    eProsima_user_DllExport void error_status(
            const MonitoringErrorStatus& _error_status);

    /*!
     * @brief This function moves the value in member error_status
     * @param _error_status New value to be moved in member error_status
     */
    eProsima_user_DllExport void error_status(
            MonitoringErrorStatus&& _error_status);

    /*!
     * @brief This function returns a constant reference to member error_status
     * @return Constant reference to member error_status
     */
    eProsima_user_DllExport const MonitoringErrorStatus& error_status() const;

    /*!
     * @brief This function returns a reference to member error_status
     * @return Reference to member error_status
     */
    eProsima_user_DllExport MonitoringErrorStatus& error_status();


    /*!
     * @brief This function sets a value in member has_errors
     * @param _has_errors New value for member has_errors
     */
    eProsima_user_DllExport void has_errors(
            bool _has_errors);

    /*!
     * @brief This function returns the value of member has_errors
     * @return Value of member has_errors
     */
    eProsima_user_DllExport bool has_errors() const;

    /*!
     * @brief This function returns a reference to member has_errors
     * @return Reference to member has_errors
     */
    eProsima_user_DllExport bool& has_errors();


    /*!
     * @brief This function returns the maximum serialized size of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(
            const MonitoringStatus& data,
            size_t current_alignment = 0);



    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(
            eprosima::fastcdr::Cdr& cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(
            eprosima::fastcdr::Cdr& cdr);




    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(
            eprosima::fastcdr::Cdr& cdr) const;

private:

    MonitoringErrorStatus m_error_status;
    bool m_has_errors;

};


#endif // _FAST_DDS_GENERATED_MONITORINGSTATUS_H_



#endif // FASTCDR_VERSION_MAJOR == 1

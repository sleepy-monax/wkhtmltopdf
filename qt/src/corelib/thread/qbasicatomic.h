/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QBASICATOMIC_H
#define QBASICATOMIC_H

#include <QtCore/qglobal.h>

#ifdef _MSC_VER
#include <intrin.h>
#endif

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Core)

class Q_CORE_EXPORT QBasicAtomicInt
{
public:
    int _q_value;

    // Non-atomic API
    inline bool operator==(int value) const
    {
        return _q_value == value;
    }

    inline bool operator!=(int value) const
    {
        return _q_value != value;
    }

    inline bool operator!() const
    {
        return _q_value == 0;
    }

    inline operator int() const
    {
        return _q_value;
    }

    inline QBasicAtomicInt &operator=(int value)
    {
        _q_value = value;
        return *this;
    }

    static bool isReferenceCountingNative() { return true; }
    static bool isReferenceCountingWaitFree() { return true; }

    #ifdef _MSC_VER
    bool ref() { return _InterlockedIncrement((volatile long *)&_q_value) != 0; }
    bool deref() { return _InterlockedDecrement((volatile long *)&_q_value) != 0; }
    #else
    bool ref() { return __atomic_add_fetch(&_q_value, 1, __ATOMIC_SEQ_CST) != 0; }
    bool deref() { return __atomic_sub_fetch(&_q_value, 1, __ATOMIC_SEQ_CST) != 0; }
    #endif

    static bool isTestAndSetNative() { return true; }
    static bool isTestAndSetWaitFree() { return true; }

    #ifdef _MSC_VER
    bool testAndSetRelaxed(int expectedValue, int newValue) { return _InterlockedCompareExchange((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    bool testAndSetAcquire(int expectedValue, int newValue) { return _InterlockedCompareExchange((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    bool testAndSetRelease(int expectedValue, int newValue) { return _InterlockedCompareExchange((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    bool testAndSetOrdered(int expectedValue, int newValue) { return _InterlockedCompareExchange((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    #else
    bool testAndSetRelaxed(int expectedValue, int newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); }
    bool testAndSetAcquire(int expectedValue, int newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_ACQUIRE, __ATOMIC_SEQ_CST); }
    bool testAndSetRelease(int expectedValue, int newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_RELEASE, __ATOMIC_SEQ_CST); }
    bool testAndSetOrdered(int expectedValue, int newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_ACQ_REL, __ATOMIC_SEQ_CST); }
    #endif

    static bool isFetchAndStoreNative() { return true; }
    static bool isFetchAndStoreWaitFree() { return true; }

    #ifdef _MSC_VER
    int fetchAndStoreRelaxed(int newValue) { return _InterlockedExchange((volatile long *)&_q_value, newValue); }
    int fetchAndStoreAcquire(int newValue) { return _InterlockedExchange((volatile long *)&_q_value, newValue); }
    int fetchAndStoreRelease(int newValue) { return _InterlockedExchange((volatile long *)&_q_value, newValue); }
    int fetchAndStoreOrdered(int newValue) { return _InterlockedExchange((volatile long *)&_q_value, newValue); }
    #else
    int fetchAndStoreRelaxed(int newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_SEQ_CST); }
    int fetchAndStoreAcquire(int newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQUIRE); }
    int fetchAndStoreRelease(int newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_RELEASE); }
    int fetchAndStoreOrdered(int newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQ_REL); }
    #endif

    static bool isFetchAndAddNative() { return true; }
    static bool isFetchAndAddWaitFree() { return true; }

    #ifdef _MSC_VER
    int fetchAndAddRelaxed(int valueToAdd) { return _InterlockedExchangeAdd((volatile long *)&_q_value, valueToAdd); }
    int fetchAndAddAcquire(int valueToAdd) { return _InterlockedExchangeAdd((volatile long *)&_q_value, valueToAdd); }
    int fetchAndAddRelease(int valueToAdd) { return _InterlockedExchangeAdd((volatile long *)&_q_value, valueToAdd); }
    int fetchAndAddOrdered(int valueToAdd) { return _InterlockedExchangeAdd((volatile long *)&_q_value, valueToAdd); }
    #else
    int fetchAndAddRelaxed(int valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_SEQ_CST); }
    int fetchAndAddAcquire(int valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_ACQUIRE); }
    int fetchAndAddRelease(int valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_RELEASE); }
    int fetchAndAddOrdered(int valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_ACQ_REL); }
    #endif
};

template <typename T>
class QBasicAtomicPointer
{
public:
    T * _q_value;

    // Non-atomic API
    inline bool operator==(T *value) const
    {
        return _q_value == value;
    }

    inline bool operator!=(T *value) const
    {
        return !operator==(value);
    }

    inline bool operator!() const
    {
        return operator==(0);
    }

    inline operator T *() const
    {
        return _q_value;
    }

    inline T *operator->() const
    {
        return _q_value;
    }

    inline QBasicAtomicPointer<T> &operator=(T *value)
    {
        _q_value = value;
        return *this;
    }

    static bool isTestAndSetNative() { return true; }
    static bool isTestAndSetWaitFree() { return true;
    }

    #ifdef _MSC_VER
    bool testAndSetRelaxed(T *expectedValue, T *newValue) { return _InterlockedCompareExchangePointer((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    bool testAndSetAcquire(T *expectedValue, T *newValue) { return _InterlockedCompareExchangePointer((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    bool testAndSetRelease(T *expectedValue, T *newValue) { return _InterlockedCompareExchangePointer((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    bool testAndSetOrdered(T *expectedValue, T *newValue) { return _InterlockedCompareExchangePointer((volatile long *)&_q_value, newValue, expectedValue) == expectedValue; }
    #else
    bool testAndSetRelaxed(T *expectedValue, T *newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); }
    bool testAndSetAcquire(T *expectedValue, T *newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_ACQUIRE, __ATOMIC_SEQ_CST); }
    bool testAndSetRelease(T *expectedValue, T *newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_RELEASE, __ATOMIC_SEQ_CST); }
    bool testAndSetOrdered(T *expectedValue, T *newValue) { return __atomic_compare_exchange_n(&_q_value, &expectedValue, newValue, false, __ATOMIC_ACQ_REL, __ATOMIC_SEQ_CST); }
    #endif

    static bool isFetchAndStoreNative() { return true; }
    static bool isFetchAndStoreWaitFree() { return true; }

    #ifdef _MSC_VER
    T *fetchAndStoreRelaxed(T *newValue) { return _InterlockedExchangePointer((volatile long *)&_q_value, newValue); }
    T *fetchAndStoreAcquire(T *newValue) { return _InterlockedExchangePointer((volatile long *)&_q_value, newValue); }
    T *fetchAndStoreRelease(T *newValue) { return _InterlockedExchangePointer((volatile long *)&_q_value, newValue); }
    T *fetchAndStoreOrdered(T *newValue) { return _InterlockedExchangePointer((volatile long *)&_q_value, newValue); }
    #else
    T *fetchAndStoreRelaxed(T *newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_SEQ_CST); }
    T *fetchAndStoreAcquire(T *newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQUIRE); }
    T *fetchAndStoreRelease(T *newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_RELEASE); }
    T *fetchAndStoreOrdered(T *newValue) { return __atomic_exchange_n(&_q_value, newValue, __ATOMIC_ACQ_REL); }
    #endif

    static bool isFetchAndAddNative() { return true; }
    static bool isFetchAndAddWaitFree() { return true; }

    #ifdef _MSC_VER
    T *fetchAndAddRelaxed(qptrdiff valueToAdd) { return _InterlockedExchangeAddPointer((volatile long *)&_q_value, valueToAdd); }
    T *fetchAndAddAcquire(qptrdiff valueToAdd) { return _InterlockedExchangeAddPointer((volatile long *)&_q_value, valueToAdd); }
    T *fetchAndAddRelease(qptrdiff valueToAdd) { return _InterlockedExchangeAddPointer((volatile long *)&_q_value, valueToAdd); }
    T *fetchAndAddOrdered(qptrdiff valueToAdd) { return _InterlockedExchangeAddPointer((volatile long *)&_q_value, valueToAdd); }
    #else
    T *fetchAndAddRelaxed(qptrdiff valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_SEQ_CST); }
    T *fetchAndAddAcquire(qptrdiff valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_ACQUIRE); }
    T *fetchAndAddRelease(qptrdiff valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_RELEASE); }
    T *fetchAndAddOrdered(qptrdiff valueToAdd) { return __atomic_add_fetch(&_q_value, valueToAdd, __ATOMIC_ACQ_REL); }
    #endif
};

#define Q_BASIC_ATOMIC_INITIALIZER(a) { (a) }

QT_END_NAMESPACE
QT_END_HEADER

#endif // QBASIC_ATOMIC

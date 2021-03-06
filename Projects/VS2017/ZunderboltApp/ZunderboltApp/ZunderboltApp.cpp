// ZunderboltApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/SInternalLogger.h"
#include "ZMemory/PoolAllocator.h"
#include "ZMath/Vector3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/Matrix4x4.h"
#include "ZContainers/ArrayDynamic.h"
#include "ZIO/MemoryStream.h"
#include "ZTime/STimeZoneFactory.h"
#include "ZTiming/DateTimeNow.h"
#include "ZThreading/Thread.h"
#include "ZThreading/SThisThread.h"
#include "ZDiagnosis/ScopedCallTraceNotifier.h"

z::Thread t(z::Delegate<void (const z::string_z&)>(z::SInternalLogger::Log), "tupadre");

int main()
{
    z::ScopedCallTraceNotifier sss(z::CallTrace("main", null_z, 0));

	z::string_z tupadre = "ouyeah\n";
	tupadre.CompareTo(tupadre, z::EComparisonType::E_BinaryCaseInsensitive);
	z::SInternalLogger::Log(tupadre + 10 + 8.55f);
	
	z::CharUnicode c = 'e';

	z::PoolAllocator pool(16, 4, z::Alignment(4));

    z::Vector3 vv(1, 0, 1);
    vv.AngleBetween(vv);

    z::TransformationMatrix<z::Matrix4x4> tm;

    z::ArrayDynamic<int> d;
    z::MemoryStream<> m(10);

    z::DateTimeNow now;
    z::SInternalLogger::Log(now.ToString());

    const z::TimeZone* pTimeZone = z::STimeZoneFactory::GetTimeZoneById("Europe/Madrid");

    
    z::SThisThread::Sleep(z::TimeSpan(500));

    return 0;
}


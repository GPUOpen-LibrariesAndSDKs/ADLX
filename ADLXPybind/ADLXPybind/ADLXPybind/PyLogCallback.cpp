// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/ILog.h"
#include <functional>


namespace py = pybind11;
using namespace adlx;


// Callback
class PyLogCallback : public IADLXLog
{
public:
	std::function<ADLX_RESULT(const wchar_t*)> m_call;

	ADLX_RESULT WriteLog(const wchar_t* msg) override
	{
		if (m_call)
			return m_call(msg);
		return ADLX_OK;
	}
};

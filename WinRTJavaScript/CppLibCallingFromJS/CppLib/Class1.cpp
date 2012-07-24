// Class1.cpp
#include "pch.h"
#include "Class1.h"
#include <ppltasks.h>
#include <concurrent_vector.h>

using namespace CppLib;
using namespace Platform;
using namespace concurrency;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

Class1::Class1()
{
}

void Class1::ComputeResultImpl(array_view<float, 1>& logs)
{
	parallel_for_each(
		logs.extent,
		[=] (index<1> idx) restrict(amp) {
			logs[idx] = concurrency::fast_math::log10(logs[idx]);	
	}
	);
}

// public API
IVector<double>^ Class1::ComputeResult(double input)
{
	// Implement your function in ISO C++ or
	// call into your C++ lib or DLL here. This example uses AMP.
	float numbers[] = { 1.0, 10.0, 60.0, 100.0, 600.0, 10000.0 };
	array_view<float, 1> logs(6, numbers);
	ComputeResultImpl(logs);

	// Return a Windows Runtime-compatible type across the ABI
	auto res = ref new Vector<double>();
	int len = safe_cast<int>(logs.extent.size());
	for(int i = 0; i < len; i++)
	{      
		res->Append(logs[i]);
	}
	return res;
}

// Determines whether the input value is prime.
bool Class1::is_prime(int n)
{
	if (n < 2)
		return false;
	for (int i = 2; i < n; ++i)
	{
		if ((n % i) == 0)
			return false;
	}
	return true;
}

IVector<int>^ Class1::SortVector(IVector<int>^ vec)
{
	std::sort(begin(vec), end(vec));
	return vec;
}

WFC::IVector<int>^ Class1::getData()
{
	WFC::IVector<int>^ data = ref new Platform::Collections::Vector<int>();
	data->Append(10);
	data->Append(20);
	data->Append(26);

	return data;
}

WFC::IVector<Folder^>^ Class1::getFolderData()
{
	WFC::IVector<Folder^>^ data = ref new Platform::Collections::Vector<Folder^>();
	Folder^ item1 = ref new Folder();
	item1->Name = L"Item1";
	data->Append(item1);

	Folder^ item2 = ref new Folder();
	item2->Name = L"Item2";
	data->Append(item2);

	Folder^ item3 = ref new Folder();
	item3->Name = L"Item3";
	data->Append(item3);

	return data;
}

WFC::IVector<Platform::Object^>^ Class1::getObjectData()
{
	WFC::IVector<Platform::Object^>^ data = ref new Platform::Collections::Vector<Platform::Object^>();
	Folder^ item1 = ref new Folder();
	item1->Name = L"Item1";
	data->Append(item1);

	Folder^ item2 = ref new Folder();
	item2->Name = L"Item2";
	data->Append(item2);

	Folder^ item3 = ref new Folder();
	item3->Name = L"Item3";
	data->Append(item3);

	return data;
}

WFC::IObservableVector<Platform::Object^>^ Class1::getObservableData()
{
	WFC::IObservableVector<Platform::Object^>^ data = ref new Platform::Collections::Vector<Platform::Object^>();
	Folder^ item1 = ref new Folder();
	item1->Name = L"Item1";
	data->Append(item1);

	Folder^ item2 = ref new Folder();
	item2->Name = L"Item2";
	data->Append(item2);

	Folder^ item3 = ref new Folder();
	item3->Name = L"Item3";
	data->Append(item3);

	return data;
}

// This method computes all primes, orders them, then returns the ordered results.
IAsyncOperationWithProgress<IVector<int>^, double>^ Class1::GetPrimesOrdered(int first, int last)
{
	return create_async([this, first, last](progress_reporter<double> reporter) -> IVector<int>^ {
		// Ensure that the input values are in range.
		if (first < 0 || last < 0) {
			throw ref new InvalidArgumentException();
		}
		// Perform the computation in parallel.
		concurrent_vector<int> primes;
		long operation = 0;
		long range = last - first + 1;
		double lastPercent = 0.0;

		parallel_for(first, last + 1, [this, &primes, &operation, range, &lastPercent, reporter](int n) {
			// Report progress message.
			double progress = 100.0 * InterlockedIncrement(&operation) / range;
			if (progress >= lastPercent)
			{
				reporter.report(progress);
				lastPercent += 1.0;
			}

			// If the value is prime, add it to the local vector.
			if (is_prime(n)) {
				primes.push_back(n);
			}
		});
		reporter.report(100.0);

		// Sort the results.
		std::sort(begin(primes), end(primes), std::less<int>());

		// Copy the results to an IVector object. The IVector
		// interface makes collections of data available to other
		// Windows Runtime components.
		IVector<int>^ results = ref new Vector<int>();
		std::for_each(std::begin(primes), std::end(primes), [&results](int prime) {
			results->Append(prime);
		});
		return results;
	});
}

// This method returns no value. Instead, it fires an event each time a prime is found, and transfers the prime through the event.
IAsyncActionWithProgress<double>^ Class1::GetPrimesUnordered(int first, int last)
{

	auto window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
	m_dispatcher = window->Dispatcher;

	return create_async([this, first, last](progress_reporter<double> reporter) {
		// Ensure that the input values are in range.
		if (first < 0 || last < 0) {
			throw ref new InvalidArgumentException();
		}
		// Perform the computation in parallel.
		concurrent_vector<int> primes;
		long operation = 0;
		long range = last - first + 1;
		double lastPercent = 0.0;

		parallel_for(first, last + 1, [this, &primes, &operation, range, &lastPercent, reporter](int n) 
		{
			// Report progress message.
			double progress = 100.0 * InterlockedIncrement(&operation) / range;
			if (progress >= lastPercent)
			{
				reporter.report(progress);
				lastPercent += 1.0;
			}

			// If the value is prime, add it to the local vector.
			if (is_prime(n))
			{
				primes.push_back(n);
				m_dispatcher->RunAsync( CoreDispatcherPriority::Normal,
					ref new DispatchedHandler([this, n]() 
				{
					this->primeFoundEvent(n);
				}, Platform::CallbackContext::Any));

			}
		});
		reporter.report(100.0);
	});
}
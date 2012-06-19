#pragma once
#include <collection.h>
#include <amp.h>
#include <amp_math.h>

namespace CppLib
{
	public delegate void PrimeFoundHandler(int i);

    public ref class Class1 sealed
    {
    public:
        Class1();

	public:
		Windows::Foundation::Collections::IVector<double>^ ComputeResult(double input);
		Windows::Foundation::IAsyncOperationWithProgress<Windows::Foundation::Collections::IVector<int>^, double>^
			GetPrimesOrdered(int first, int last);
		bool is_prime(int n);
	public:
		Windows::Foundation::IAsyncActionWithProgress<double>^ Class1::GetPrimesUnordered(int first, int last);
		event PrimeFoundHandler^ primeFoundEvent;
	private:
		void ComputeResultImpl(concurrency::array_view<float, 1>&);
	private:
		Windows::UI::Core::CoreDispatcher^ m_dispatcher;
    };
}
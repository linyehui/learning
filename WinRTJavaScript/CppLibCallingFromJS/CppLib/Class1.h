#pragma once
#include <collection.h>
#include <amp.h>
#include <amp_math.h>

namespace WFC = Windows::Foundation::Collections;

namespace CppLib
{
	public delegate void PrimeFoundHandler(int i);

	public ref class Folder sealed
	{
	private:
		Platform::String^ m_Name;

	public:	
		Folder()
		{

		}

		property Platform::String^ Name
		{
			Platform::String^ get()
			{
				return m_Name;
			}
			void set(Platform::String^ value)
			{
				if(m_Name != value)
				{
					m_Name = value;
				}
			}
		};	
	};

    public ref class Class1 sealed
    {
    public:
        Class1();


	public:
		WFC::IVector<double>^ ComputeResult(double input);
		Windows::Foundation::IAsyncOperationWithProgress<WFC::IVector<int>^, double>^
			GetPrimesOrdered(int first, int last);
		bool is_prime(int n);

		WFC::IVector<int>^ SortVector(WFC::IVector<int>^ vec);
		WFC::IVector<int>^ getData();
		WFC::IVector<Folder^>^ getFolderData();
		WFC::IVector<Platform::Object^>^ getObjectData();
		WFC::IObservableVector<Platform::Object^>^ getObservableData();
	public:
		Windows::Foundation::IAsyncActionWithProgress<double>^ Class1::GetPrimesUnordered(int first, int last);
		event PrimeFoundHandler^ primeFoundEvent;
	private:
		void ComputeResultImpl(concurrency::array_view<float, 1>&);
	private:
		Windows::UI::Core::CoreDispatcher^ m_dispatcher;
    };
}
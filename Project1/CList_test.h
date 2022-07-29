#pragma once
#include <assert.h>

template <typename T>
struct tNodeList
{
	tNodeList<T>* m_PrevPtr;
	tNodeList<T>* m_NextPtr;
	T m_Data;

	tNodeList()
	{
	}

	tNodeList(tNodeList<T>* _PrevPtr, tNodeList<T>* _NextPtr, const T& _Data)
		: m_PrevPtr(_PrevPtr)
		, m_NextPtr(_NextPtr)
		, m_Data(_Data)
	{
	}

};

template <typename T>
class CList
{
private:
	tNodeList<T>* m_HeadPtr;
	tNodeList<T>* m_EndPtr;
	int m_Count;
public:
	CList()
		: m_HeadPtr(nullptr)
		, m_EndPtr(nullptr)
		, m_Count(0)
	{
	}

	~CList()
	{
	}
	class iterator;
public:
	iterator begin();
	iterator end();
	iterator insert(const iterator& _Iter, const T& _Data);
	iterator erase(const iterator& _Iter);


public:
	void Push_Back(const T& _Data);

	void Push_Front(const T& _Data);

	class iterator
	{
	private:
		tNodeList<T> I_Node;
		CList<T> I_List;
		bool IsValid;

	public:
		iterator()
			: I_Node(nullptr)
			, I_List(nullptr)
			, IsValid(false)
		{
		}

		iterator(tNodeList<T> _Node, CList<T> _List)
			: I_Node(_Node)
			, I_List(_List)
			, IsValid(false)
		{
			if (nullptr != I_List && nullptr != I_Node)
			{
				IsValid = true;
			}
		}

		~iterator()
		{
		}

	public:
		T& operator* ()
		{
			return I_Node->m_Data;
		}

		iterator& operator++()
		{
			if (end() == I_Node)
			{
				assert(nullptr);
			}
			else
			{
				I_Node = I_Node->m_NextPtr;
			}
			return *this;
		}



		iterator& operator++(int)
		{
			iterator Copy_Iter = *this;
			++(*this);
			return Copy_Iter;
		}

		bool operator==(const iterator& _other)
		{
			if (I_List == _other.I_List && I_Node == _other.I_Node)
			{
				return true;
			}

			return false;
		}

		bool operator!=(const iterator& _other)
		{

			return !(*this == _other);
		}

		friend class CList;

		
	};

};

template<typename T>
void CList<T>::Push_Back(const T& _Data)
{
	tNodeList<T>* NewPtr = new tNodeList<T>(_nullptr, _nullptr, _Data);
	if (0 == m_Count)
	{
		m_HeadPtr = NewPtr;
		m_EndPtr = NewPtr;
	}

	else
	{
		m_EndPtr->m_NextPtr = NewPtr;
		NewPtr->m_PrevPtr = m_EndPtr;
		m_EndPtr = NewPtr;
	}
	++m_Count;
}

template<typename T>
void CList<T>::Push_Front(const T& _Data)
{
	tNodeList<T>* NewPtr = new tNodeList<T>(_nullptr, _nullptr, _Data);
	if (0 == m_Count)
	{
		m_HeadPtr = NewPtr;
		m_EndPtr = NewPtr;
	}
	
	else
	{
		m_HeadPtr->m_PrevPtr = NewPtr;

		NewPtr->m_NextPtr = m_HeaPtr;
		m_HeadPtr = NewPtr;
	}
	++m_Count;
}


#pragma once
#include <assert.h>

template <typename T>
struct tNodeList
{
	tNodeList<T>* m_PrevPtr;
	tNodeList<T>* m_NextPtr;
	T m_Data;

	tNodeList()
		: m_PrevPtr(nullptr)
		, m_NextPtr(nullptr)
		, m_Data()
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

private:
	tNodeList<T>* m_HeadPtr;
	tNodeList<T>* m_EndPtr;
	int m_Count;

public:
	void Push_Back(const T& _Data);

	void Push_Front(const T& _Data);

	
public:
	class Iterator;
	Iterator begin();
	Iterator end();
	Iterator insert(const Iterator& _Iter, const T& _Data);
	/*Iterator find();*/
	Iterator erase(const Iterator& _Iter);

	class Iterator
	{
	private:
		CList<T>* IterList;
		tNodeList<T>* IterNode;
		bool Isvalid;
	public:
		Iterator()
			: IterList(nullptr)
			, IterNode(nullptr)
			, Isvalid(false)
		{

		}
		Iterator(CList<T>* _IterList, tNodeList<T>* _IterNode)
			: IterList(_IterList)
			, IterNode(_IterNode)
			, Isvalid(false)
		{
			if (nullptr != IterList && nullptr != IterNode)
			{
				Isvalid = true;
			}

		}

		~Iterator()
		{
		}



	public:
		T& operator* ()
		{
			return IterNode->m_Data;
		}

		// Class에서 자기 자신이므로 파라미터가 없구나

		bool operator==(const Iterator& _Other)
		{
			if (IterList == _Other.IterList && IterNode == _Other.IterNode)
			{
				return true;
			}

			return false;
		}

		bool operator!=(const Iterator& _Other)
		{
			return !(*this == _Other);
		}

		Iterator& operator++()
		{
			if (nullptr == IterNode || !Isvalid)
			{
				assert(nullptr);
			}

			IterNode = IterNode->m_NextPtr;

			return *this;


		}

		Iterator& operator++(int)
		{
			Iterator CopyIter = *this;
			++(*this);
			return CopyIter;
		}


		friend class CList;
	};
};



template<typename T>
void CList<T>::Push_Back(const T& _Data)
{
	tNodeList<T>* NewPtr = new tNodeList<T>(nullptr, nullptr, _Data);
	if (0 == m_Count)
	{
		m_HeadPtr = NewPtr;
		m_EndPtr = NewPtr;
	}

	else
	{
		NewPtr->m_PrevPtr = m_EndPtr;
		m_EndPtr->m_NextPtr = NewPtr;
		m_EndPtr = NewPtr;
	}

	++m_Count;
}

template<typename T>
void CList<T>::Push_Front(const T& _Data)
{
	tNodeList<T>* NewPtr = new tNodeList<T>(nullptr, nullptr, _Data);
	if (0 == m_Count)
	{
		m_HeadPtr = NewPtr;
		m_EndPtr = NewPtr;
	}

	else
	{
		NewPtr->m_NextPtr = m_HeadPtr;
		m_HeadPtr->m_PrevPtr = NewPtr;
		m_HeadPtr = NewPtr;
	}
}

template <typename T>
typename CList<T>::Iterator CList<T>::begin()
{
	return Iterator(this, m_HeadPtr);
}

template <typename T>
typename CList<T>::Iterator CList<T>::end()
{
	return Iterator(this, nullptr);
}

template <typename T>
typename CList<T>::Iterator CList<T>::insert(const Iterator& _Iter, const T& _Data)
{
	tNodeList<T>* NewPtr = new tNodeList<T>(nullptr, nullptr, _Data);
	if (end() == _Iter)
	{
		NewPtr->m_PrevPtr = _Iter.IterList->m_EndPtr;
		_Iter.IterList->m_EndPtr->m_NextPtr = NewPtr;
		NewPtr->m_NextPtr = nullptr;

	}
	else if (begin() == _Iter)
	{
		m_HeadPtr->m_PrevPtr = NewPtr;
		NewPtr->m_NextPtr = m_HeadPtr;
		m_HeadPtr = NewPtr;
	}

	else
	{
		NewPtr->m_PrevPtr = _Iter.IterNode->m_PrevPtr;
		_Iter.IterNode->m_PrevPtr = NewPtr;
		NewPtr->m_NextPtr = _Iter.IterNode;
	}

	++m_Count;
	return Iterator(this, NewPtr);
}

template<typename T>
typename CList<T>::Iterator CList<T>::erase(const Iterator& _Iter)
{
	tNodeList<T>* NewPtr = new tNodeList<T>();
	if (end() == _Iter || 1 == m_Count )
	{
		assert(nullptr);
	}

	else if (begin() == _Iter)
	{
		m_HeadPtr->m_NextPtr->m_PrevPtr = nullptr;
		m_HeadPtr = m_HeadPtr->m_NextPtr;
		NewPtr = m_HeadPtr;
		
		
		
	}

	else
	{
		NewPtr->m_PrevPtr->m_NextPtr = NewPtr->m_NextPtr;
		NewPtr->m_NextPtr->m_PrevPtr = NewPtr->m_PrevPtr;
		NewPtr = NewPtr-> m_NextPtr;

	}
	--m_Count;
	return Iterator(this, NewPtr);
}

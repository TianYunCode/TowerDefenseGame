#pragma once

template <typename T>
class Manager
{
public:
	static T* instance()
	{
		if (!s_instance)
		{
			s_instance = new T();
		}

		return s_instance;
	}

private:
	static T* s_instance;

protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

template <typename T>
T* Manager<T>::s_instance = nullptr;

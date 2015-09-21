#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton
{
protected:
    static T* m_instance;

public:
    inline static T* GetInstance() { return m_instance; }

    static T* create()
    {
        if(!m_instance)
        {
            m_instance = new T();
        }
        return m_instance;
    }

    static void destroy()
    {
        delete Singleton<T>::m_instance;
        Singleton<T>::m_instance = nullptr;
    }


private:

    Singleton(Singleton const&)=delete;
    Singleton& operator=(Singleton const&)=delete;

protected:
    Singleton() {  }
    ~Singleton() {  }
};

template<typename T> T* Singleton<T>::m_instance = nullptr;


#endif //SINGLETON_H

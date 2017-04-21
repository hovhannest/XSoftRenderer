/*
 * Singleton.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <stdio.h>

template <class AType> class Singleton
{
public:
	/**
	*  @brief
	*    Returns the class instance
	*
	*  @return
	*    Pointer to the instance, assumed to be never a null pointer
	*
	*  @note
	*    - Returns a pointer to the singleton instance.
	*      The instance will be created if it has not been created before.
	*    - The returned pointer can be a null pointer if the instance has already
	*      been destroyed, that is on deinitialization of the program.
	*      So be careful when using a singleton during deinitialization
	*      of the program, or better - don't do it :-)
	*/
	static AType *GetInstance();

	/**
	*  @brief
	*    Returns whether or not there's an instance
	*
	*  @return
	*    'true' if there's an instance, else 'false'
	*/
	static bool HasInstance();


	static void Create();
	static void Destroy();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
protected:
	/**
	*  @brief
	*    Constructor
	*/
	Singleton();

	/**
	*  @brief
	*    Destructor
	*/
	virtual ~Singleton();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
private:
	/**
	*  @brief
	*    Destruction guard, deletes a singleton on deinitialization
	*/
	class __Destruction_Guard {
	public:
		__Destruction_Guard()
		{
		}
		~__Destruction_Guard()
		{
			if (Singleton<AType>::__Instance) {
				// Don't use reinterpret_cast in here or hell breaks loose when starting programs
				delete static_cast<Singleton<AType>*>(Singleton<AType>::__Instance);
			}
		}
		inline void init() {}
	};

	// Static data
	static __Destruction_Guard __Guard;	/**< Destroys the object on shutdown */
	static AType *__Instance;			/**< Pointer to the singleton instance, can be a null pointer */
	static bool __Destroyed;			/**< Destruction flag - set only on shutdown */

	// Undefined methods to prevent usage
	Singleton(const Singleton&);
	Singleton& operator =(Singleton);


};

template <class AType> typename Singleton<AType>::__Destruction_Guard Singleton<AType>::__Guard;
template <class AType> AType *Singleton<AType>::__Instance = NULL;
template <class AType> bool   Singleton<AType>::__Destroyed = false;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the class instance
*/
template <class AType> AType *Singleton<AType>::GetInstance()
{
	// [HACK] This is necessary for the compiler to instantiate __Guard
	__Guard.init();

	// Check if the instance must be created
	if (!__Instance && !__Destroyed) {
		// Create instance
		return new AType();
	}
	else {
		// Return instance
		return __Instance;
	}
}


template <class AType>
void Singleton<AType>::Create()
{
	Singleton<AType>::GetInstance();
}


template <class AType>
void Singleton<AType>::Destroy()
{
	delete static_cast<Singleton<AType>*>(Singleton<AType>::__Instance);
}


/**
*  @brief
*    Returns whether or not there's an instance
*/
template <class AType> bool Singleton<AType>::HasInstance()
{
	return (__Instance != NULL);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType> Singleton<AType>::Singleton()
{
	// Register instance - Don't use reinterpret_cast in here or hell breaks loose when starting programs
	__Instance = static_cast<AType*>(this);
}

/**
*  @brief
*    Destructor
*/
template <class AType> Singleton<AType>::~Singleton()
{
	// Unregister instance
	if (__Instance == this) {
		__Instance = NULL;
		__Destroyed = true;
	}
}

#endif /* SINGLETON_H_ */

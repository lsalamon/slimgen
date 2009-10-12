/*
* Copyright (c) 2007-2009 SlimGen Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#pragma once

namespace SlimGen {
	struct DefaultRefCountTrait {
	public:
		ULONG AddRef() {
			return InterlockedIncrement(&refCount);
		}
		ULONG Release() {
			return InterlockedDecrement(&refCount);
		}
	private:
		ULONG refCount;
	};

	struct NullType {};
	
	template<class T, class Interface1, class Interface2 = NullType>
	struct DefaultQIPredicate {
		static bool QueryInterface(REFIID riid, T* ptr, void** result) {
			if(riid == IID_IUnknown) {
				*result = static_cast<IUnknown*>(ptr);
				return true;
			}
			if(riid == __uuidof(Interface1)) {
				*result = static_cast<Interface1*>(ptr);
				return true;
			}
			if(riid == __uuidof(Interface2)) {
				*result = static_cast<Interface2*>(ptr);
				return true;
			}
			*result = 0;
			return false;
		}
	};

	template<class T, class Interface1>
	struct DefaultQIPredicate<T, Interface1, NullType> {
		static bool QueryInterface(REFIID riid, T* ptr, void** result) {
			if(riid == IID_IUnknown) {
				*result = static_cast<IUnknown*>(ptr);
				return true;
			}
			if(riid == __uuidof(Interface1)) {
				*result = static_cast<Interface1*>(ptr);
				return true;
			}
			*result = 0;
			return false;
		}
	};

	template<class T, class Interface, class RefCountTraits = DefaultRefCountTrait, class QIPredicate = DefaultQIPredicate<T, Interface> >
	class SlimGenUnknown : public Interface {
	private:
		RefCountTraits trait;
	public:
		SlimGenUnknown() { trait.AddRef(); }
		STDMETHOD_(ULONG,AddRef)() {
			return trait.AddRef();
		}
		STDMETHOD_(ULONG,Release)() {
			ULONG result = trait.Release();
			if(!result) {
				OnCleanup();
				delete this;
			}

			return result;
		}
		STDMETHOD(QueryInterface)(REFIID riid, __RPC__deref_out void **ppvObject) {
			if(QIPredicate::QueryInterface(riid, static_cast<T*>(this), ppvObject))
				return S_OK;
			return E_NOINTERFACE;
		}
	private:
		virtual void OnCleanup() {
		}
	};
}
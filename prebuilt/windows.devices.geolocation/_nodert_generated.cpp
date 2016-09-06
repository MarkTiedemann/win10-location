// Copyright (c) Microsoft Corporation
// All rights reserved. 
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Handle;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Devices { namespace Geolocation { 

  v8::Local<v8::Value> WrapIGeoshape(::Windows::Devices::Geolocation::IGeoshape^ wintRtInstance);
  ::Windows::Devices::Geolocation::IGeoshape^ UnwrapIGeoshape(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeopoint(::Windows::Devices::Geolocation::Geopoint^ wintRtInstance);
  ::Windows::Devices::Geolocation::Geopoint^ UnwrapGeopoint(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeopath(::Windows::Devices::Geolocation::Geopath^ wintRtInstance);
  ::Windows::Devices::Geolocation::Geopath^ UnwrapGeopath(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeoboundingBox(::Windows::Devices::Geolocation::GeoboundingBox^ wintRtInstance);
  ::Windows::Devices::Geolocation::GeoboundingBox^ UnwrapGeoboundingBox(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeocoordinateSatelliteData(::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ wintRtInstance);
  ::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ UnwrapGeocoordinateSatelliteData(Local<Value> value);
  
  v8::Local<v8::Value> WrapVenueData(::Windows::Devices::Geolocation::VenueData^ wintRtInstance);
  ::Windows::Devices::Geolocation::VenueData^ UnwrapVenueData(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeocoordinate(::Windows::Devices::Geolocation::Geocoordinate^ wintRtInstance);
  ::Windows::Devices::Geolocation::Geocoordinate^ UnwrapGeocoordinate(Local<Value> value);
  
  v8::Local<v8::Value> WrapCivicAddress(::Windows::Devices::Geolocation::CivicAddress^ wintRtInstance);
  ::Windows::Devices::Geolocation::CivicAddress^ UnwrapCivicAddress(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeoposition(::Windows::Devices::Geolocation::Geoposition^ wintRtInstance);
  ::Windows::Devices::Geolocation::Geoposition^ UnwrapGeoposition(Local<Value> value);
  
  v8::Local<v8::Value> WrapPositionChangedEventArgs(::Windows::Devices::Geolocation::PositionChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Geolocation::PositionChangedEventArgs^ UnwrapPositionChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapStatusChangedEventArgs(::Windows::Devices::Geolocation::StatusChangedEventArgs^ wintRtInstance);
  ::Windows::Devices::Geolocation::StatusChangedEventArgs^ UnwrapStatusChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeolocator(::Windows::Devices::Geolocation::Geolocator^ wintRtInstance);
  ::Windows::Devices::Geolocation::Geolocator^ UnwrapGeolocator(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeocircle(::Windows::Devices::Geolocation::Geocircle^ wintRtInstance);
  ::Windows::Devices::Geolocation::Geocircle^ UnwrapGeocircle(Local<Value> value);
  


  static void InitPositionAccuracyEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PositionAccuracy").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionAccuracy::Default)));
	Nan::Set(enumObject, Nan::New<String>("high").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionAccuracy::High)));
  }


  static void InitPositionStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PositionStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("ready").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionStatus::Ready)));
	Nan::Set(enumObject, Nan::New<String>("initializing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionStatus::Initializing)));
	Nan::Set(enumObject, Nan::New<String>("noData").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionStatus::NoData)));
	Nan::Set(enumObject, Nan::New<String>("disabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionStatus::Disabled)));
	Nan::Set(enumObject, Nan::New<String>("notInitialized").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionStatus::NotInitialized)));
	Nan::Set(enumObject, Nan::New<String>("notAvailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionStatus::NotAvailable)));
  }


  static void InitPositionSourceEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PositionSource").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("cellular").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::Cellular)));
	Nan::Set(enumObject, Nan::New<String>("satellite").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::Satellite)));
	Nan::Set(enumObject, Nan::New<String>("wiFi").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::WiFi)));
	Nan::Set(enumObject, Nan::New<String>("iPAddress").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::IPAddress)));
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::Default)));
	Nan::Set(enumObject, Nan::New<String>("obfuscated").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::PositionSource::Obfuscated)));
  }


  static void InitGeoshapeTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GeoshapeType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("geopoint").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeoshapeType::Geopoint)));
	Nan::Set(enumObject, Nan::New<String>("geocircle").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeoshapeType::Geocircle)));
	Nan::Set(enumObject, Nan::New<String>("geopath").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeoshapeType::Geopath)));
	Nan::Set(enumObject, Nan::New<String>("geoboundingBox").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeoshapeType::GeoboundingBox)));
  }


  static void InitAltitudeReferenceSystemEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("AltitudeReferenceSystem").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::AltitudeReferenceSystem::Unspecified)));
	Nan::Set(enumObject, Nan::New<String>("terrain").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::AltitudeReferenceSystem::Terrain)));
	Nan::Set(enumObject, Nan::New<String>("ellipsoid").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::AltitudeReferenceSystem::Ellipsoid)));
	Nan::Set(enumObject, Nan::New<String>("geoid").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::AltitudeReferenceSystem::Geoid)));
	Nan::Set(enumObject, Nan::New<String>("surface").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::AltitudeReferenceSystem::Surface)));
  }


  static void InitGeolocationAccessStatusEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("GeolocationAccessStatus").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unspecified").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeolocationAccessStatus::Unspecified)));
	Nan::Set(enumObject, Nan::New<String>("allowed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeolocationAccessStatus::Allowed)));
	Nan::Set(enumObject, Nan::New<String>("denied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Devices::Geolocation::GeolocationAccessStatus::Denied)));
  }



  
  static bool IsBasicGeopositionJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("latitude").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber())
      {
          return false;
      }
    }
    
    symbol = Nan::New<String>("longitude").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber())
      {
          return false;
      }
    }
    
    symbol = Nan::New<String>("altitude").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber())
      {
          return false;
      }
    }
    
    return true;
  }

  ::Windows::Devices::Geolocation::BasicGeoposition BasicGeopositionFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Devices::Geolocation::BasicGeoposition returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("latitude").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Latitude = Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0);
    }
    
    symbol = Nan::New<String>("longitude").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Longitude = Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0);
    }
    
    symbol = Nan::New<String>("altitude").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Altitude = Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0);
    }
    
    return returnValue;
  }

  Local<Value> BasicGeopositionToJsObject(::Windows::Devices::Geolocation::BasicGeoposition value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("latitude").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.Latitude)));
    Nan::Set(obj, Nan::New<String>("longitude").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.Longitude)));
    Nan::Set(obj, Nan::New<String>("altitude").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.Altitude)));
    
    return scope.Escape(obj);
  }

  
  class IGeoshape : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IGeoshape").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitudeReferenceSystem").ToLocalChecked(), AltitudeReferenceSystemGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("geoshapeType").ToLocalChecked(), GeoshapeTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("spatialReferenceId").ToLocalChecked(), SpatialReferenceIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("IGeoshape").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IGeoshape(::Windows::Devices::Geolocation::IGeoshape^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::IGeoshape^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::IGeoshape^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::IGeoshape^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IGeoshape *wrapperInstance = new IGeoshape(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void AltitudeReferenceSystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::IGeoshape^>(info.This()))
      {
        return;
      }

      IGeoshape *wrapper = IGeoshape::Unwrap<IGeoshape>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::AltitudeReferenceSystem result = wrapper->_instance->AltitudeReferenceSystem;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GeoshapeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::IGeoshape^>(info.This()))
      {
        return;
      }

      IGeoshape *wrapper = IGeoshape::Unwrap<IGeoshape>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::GeoshapeType result = wrapper->_instance->GeoshapeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SpatialReferenceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::IGeoshape^>(info.This()))
      {
        return;
      }

      IGeoshape *wrapper = IGeoshape::Unwrap<IGeoshape>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->SpatialReferenceId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::IGeoshape^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIGeoshape(::Windows::Devices::Geolocation::IGeoshape^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::IGeoshape^ UnwrapIGeoshape(Local<Value> value);
  };
  Persistent<FunctionTemplate> IGeoshape::s_constructorTemplate;

  v8::Local<v8::Value> WrapIGeoshape(::Windows::Devices::Geolocation::IGeoshape^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IGeoshape::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::IGeoshape^ UnwrapIGeoshape(Local<Value> value)
  {
     return IGeoshape::Unwrap<IGeoshape>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIGeoshape(Local<Object> exports)
  {
    IGeoshape::Init(exports);
  }

  class Geopoint : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Geopoint").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitudeReferenceSystem").ToLocalChecked(), AltitudeReferenceSystemGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("geoshapeType").ToLocalChecked(), GeoshapeTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("spatialReferenceId").ToLocalChecked(), SpatialReferenceIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("Geopoint").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Geopoint(::Windows::Devices::Geolocation::Geopoint^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::Geopoint^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopoint^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::Geopoint^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && IsBasicGeopositionJsObject(info[0]))
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geopoint(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && IsBasicGeopositionJsObject(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg1 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geopoint(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && IsBasicGeopositionJsObject(info[0])
        && info[1]->IsInt32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg1 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geopoint(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Geopoint *wrapperInstance = new Geopoint(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopoint^>(info.This()))
      {
        return;
      }

      Geopoint *wrapper = Geopoint::Unwrap<Geopoint>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::BasicGeoposition result = wrapper->_instance->Position;
        info.GetReturnValue().Set(BasicGeopositionToJsObject(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AltitudeReferenceSystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopoint^>(info.This()))
      {
        return;
      }

      Geopoint *wrapper = Geopoint::Unwrap<Geopoint>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::AltitudeReferenceSystem result = wrapper->_instance->AltitudeReferenceSystem;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GeoshapeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopoint^>(info.This()))
      {
        return;
      }

      Geopoint *wrapper = Geopoint::Unwrap<Geopoint>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::GeoshapeType result = wrapper->_instance->GeoshapeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SpatialReferenceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopoint^>(info.This()))
      {
        return;
      }

      Geopoint *wrapper = Geopoint::Unwrap<Geopoint>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->SpatialReferenceId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::Geopoint^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeopoint(::Windows::Devices::Geolocation::Geopoint^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::Geopoint^ UnwrapGeopoint(Local<Value> value);
  };
  Persistent<FunctionTemplate> Geopoint::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeopoint(::Windows::Devices::Geolocation::Geopoint^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Geopoint::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::Geopoint^ UnwrapGeopoint(Local<Value> value)
  {
     return Geopoint::Unwrap<Geopoint>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeopoint(Local<Object> exports)
  {
    Geopoint::Init(exports);
  }

  class Geopath : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Geopath").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("positions").ToLocalChecked(), PositionsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitudeReferenceSystem").ToLocalChecked(), AltitudeReferenceSystemGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("geoshapeType").ToLocalChecked(), GeoshapeTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("spatialReferenceId").ToLocalChecked(), SpatialReferenceIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("Geopath").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Geopath(::Windows::Devices::Geolocation::Geopath^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::Geopath^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopath^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::Geopath^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Geolocation::BasicGeoposition>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return IsBasicGeopositionJsObject(value);
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
                   return BasicGeopositionFromJsObject(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geopath(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Geolocation::BasicGeoposition>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return IsBasicGeopositionJsObject(value);
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
                   return BasicGeopositionFromJsObject(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg1 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geopath(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsInt32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Geolocation::BasicGeoposition>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return IsBasicGeopositionJsObject(value);
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
                   return BasicGeopositionFromJsObject(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg1 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geopath(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Geopath *wrapperInstance = new Geopath(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void PositionsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopath^>(info.This()))
      {
        return;
      }

      Geopath *wrapper = Geopath::Unwrap<Geopath>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Geolocation::BasicGeoposition>^ result = wrapper->_instance->Positions;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Geolocation::BasicGeoposition>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Geolocation::BasicGeoposition val) -> Local<Value> {
              return BasicGeopositionToJsObject(val);
            },
            [](Local<Value> value) -> bool {
              return IsBasicGeopositionJsObject(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
              return BasicGeopositionFromJsObject(value);
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AltitudeReferenceSystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopath^>(info.This()))
      {
        return;
      }

      Geopath *wrapper = Geopath::Unwrap<Geopath>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::AltitudeReferenceSystem result = wrapper->_instance->AltitudeReferenceSystem;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GeoshapeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopath^>(info.This()))
      {
        return;
      }

      Geopath *wrapper = Geopath::Unwrap<Geopath>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::GeoshapeType result = wrapper->_instance->GeoshapeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SpatialReferenceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geopath^>(info.This()))
      {
        return;
      }

      Geopath *wrapper = Geopath::Unwrap<Geopath>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->SpatialReferenceId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::Geopath^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeopath(::Windows::Devices::Geolocation::Geopath^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::Geopath^ UnwrapGeopath(Local<Value> value);
  };
  Persistent<FunctionTemplate> Geopath::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeopath(::Windows::Devices::Geolocation::Geopath^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Geopath::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::Geopath^ UnwrapGeopath(Local<Value> value)
  {
     return Geopath::Unwrap<Geopath>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeopath(Local<Object> exports)
  {
    Geopath::Init(exports);
  }

  class GeoboundingBox : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GeoboundingBox").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("center").ToLocalChecked(), CenterGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxAltitude").ToLocalChecked(), MaxAltitudeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("minAltitude").ToLocalChecked(), MinAltitudeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("northwestCorner").ToLocalChecked(), NorthwestCornerGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("southeastCorner").ToLocalChecked(), SoutheastCornerGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitudeReferenceSystem").ToLocalChecked(), AltitudeReferenceSystemGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("geoshapeType").ToLocalChecked(), GeoshapeTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("spatialReferenceId").ToLocalChecked(), SpatialReferenceIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetMethod(constructor, "tryCompute", TryCompute);

      Nan::Set(exports, Nan::New<String>("GeoboundingBox").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GeoboundingBox(::Windows::Devices::Geolocation::GeoboundingBox^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::GeoboundingBox^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::GeoboundingBox^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && IsBasicGeopositionJsObject(info[0])
        && IsBasicGeopositionJsObject(info[1]))
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          ::Windows::Devices::Geolocation::BasicGeoposition arg1 = BasicGeopositionFromJsObject(info[1]);
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::GeoboundingBox(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && IsBasicGeopositionJsObject(info[0])
        && IsBasicGeopositionJsObject(info[1])
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          ::Windows::Devices::Geolocation::BasicGeoposition arg1 = BasicGeopositionFromJsObject(info[1]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg2 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::GeoboundingBox(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && IsBasicGeopositionJsObject(info[0])
        && IsBasicGeopositionJsObject(info[1])
        && info[2]->IsInt32()
        && info[3]->IsUint32())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          ::Windows::Devices::Geolocation::BasicGeoposition arg1 = BasicGeopositionFromJsObject(info[1]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg2 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          unsigned int arg3 = static_cast<unsigned int>(Nan::To<uint32_t>(info[3]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::GeoboundingBox(arg0,arg1,arg2,arg3);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      GeoboundingBox *wrapperInstance = new GeoboundingBox(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  


    static void TryCompute(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Geolocation::BasicGeoposition>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return IsBasicGeopositionJsObject(value);
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
                   return BasicGeopositionFromJsObject(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Windows::Devices::Geolocation::GeoboundingBox^ result;
          result = ::Windows::Devices::Geolocation::GeoboundingBox::TryCompute(arg0);
          info.GetReturnValue().Set(WrapGeoboundingBox(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Geolocation::BasicGeoposition>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return IsBasicGeopositionJsObject(value);
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
                   return BasicGeopositionFromJsObject(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg1 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          ::Windows::Devices::Geolocation::GeoboundingBox^ result;
          result = ::Windows::Devices::Geolocation::GeoboundingBox::TryCompute(arg0, arg1);
          info.GetReturnValue().Set(WrapGeoboundingBox(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsInt32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Devices::Geolocation::BasicGeoposition>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return IsBasicGeopositionJsObject(value);
                 },
                 [](Local<Value> value) -> ::Windows::Devices::Geolocation::BasicGeoposition {
                   return BasicGeopositionFromJsObject(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Devices::Geolocation::BasicGeoposition>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg1 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          ::Windows::Devices::Geolocation::GeoboundingBox^ result;
          result = ::Windows::Devices::Geolocation::GeoboundingBox::TryCompute(arg0, arg1, arg2);
          info.GetReturnValue().Set(WrapGeoboundingBox(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CenterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::BasicGeoposition result = wrapper->_instance->Center;
        info.GetReturnValue().Set(BasicGeopositionToJsObject(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaxAltitudeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        double result = wrapper->_instance->MaxAltitude;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MinAltitudeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        double result = wrapper->_instance->MinAltitude;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NorthwestCornerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::BasicGeoposition result = wrapper->_instance->NorthwestCorner;
        info.GetReturnValue().Set(BasicGeopositionToJsObject(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SoutheastCornerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::BasicGeoposition result = wrapper->_instance->SoutheastCorner;
        info.GetReturnValue().Set(BasicGeopositionToJsObject(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AltitudeReferenceSystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::AltitudeReferenceSystem result = wrapper->_instance->AltitudeReferenceSystem;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GeoshapeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::GeoshapeType result = wrapper->_instance->GeoshapeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SpatialReferenceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeoboundingBox^>(info.This()))
      {
        return;
      }

      GeoboundingBox *wrapper = GeoboundingBox::Unwrap<GeoboundingBox>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->SpatialReferenceId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::GeoboundingBox^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeoboundingBox(::Windows::Devices::Geolocation::GeoboundingBox^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::GeoboundingBox^ UnwrapGeoboundingBox(Local<Value> value);
  };
  Persistent<FunctionTemplate> GeoboundingBox::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeoboundingBox(::Windows::Devices::Geolocation::GeoboundingBox^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GeoboundingBox::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::GeoboundingBox^ UnwrapGeoboundingBox(Local<Value> value)
  {
     return GeoboundingBox::Unwrap<GeoboundingBox>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeoboundingBox(Local<Object> exports)
  {
    GeoboundingBox::Init(exports);
  }

  class GeocoordinateSatelliteData : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("GeocoordinateSatelliteData").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("horizontalDilutionOfPrecision").ToLocalChecked(), HorizontalDilutionOfPrecisionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("positionDilutionOfPrecision").ToLocalChecked(), PositionDilutionOfPrecisionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("verticalDilutionOfPrecision").ToLocalChecked(), VerticalDilutionOfPrecisionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("GeocoordinateSatelliteData").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    GeocoordinateSatelliteData(::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeocoordinateSatelliteData^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::GeocoordinateSatelliteData^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      GeocoordinateSatelliteData *wrapperInstance = new GeocoordinateSatelliteData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void HorizontalDilutionOfPrecisionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeocoordinateSatelliteData^>(info.This()))
      {
        return;
      }

      GeocoordinateSatelliteData *wrapper = GeocoordinateSatelliteData::Unwrap<GeocoordinateSatelliteData>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->HorizontalDilutionOfPrecision;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionDilutionOfPrecisionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeocoordinateSatelliteData^>(info.This()))
      {
        return;
      }

      GeocoordinateSatelliteData *wrapper = GeocoordinateSatelliteData::Unwrap<GeocoordinateSatelliteData>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->PositionDilutionOfPrecision;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void VerticalDilutionOfPrecisionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::GeocoordinateSatelliteData^>(info.This()))
      {
        return;
      }

      GeocoordinateSatelliteData *wrapper = GeocoordinateSatelliteData::Unwrap<GeocoordinateSatelliteData>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->VerticalDilutionOfPrecision;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeocoordinateSatelliteData(::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ UnwrapGeocoordinateSatelliteData(Local<Value> value);
  };
  Persistent<FunctionTemplate> GeocoordinateSatelliteData::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeocoordinateSatelliteData(::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GeocoordinateSatelliteData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ UnwrapGeocoordinateSatelliteData(Local<Value> value)
  {
     return GeocoordinateSatelliteData::Unwrap<GeocoordinateSatelliteData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeocoordinateSatelliteData(Local<Object> exports)
  {
    GeocoordinateSatelliteData::Init(exports);
  }

  class VenueData : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("VenueData").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("level").ToLocalChecked(), LevelGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("VenueData").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    VenueData(::Windows::Devices::Geolocation::VenueData^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::VenueData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::VenueData^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::VenueData^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      VenueData *wrapperInstance = new VenueData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::VenueData^>(info.This()))
      {
        return;
      }

      VenueData *wrapper = VenueData::Unwrap<VenueData>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::VenueData^>(info.This()))
      {
        return;
      }

      VenueData *wrapper = VenueData::Unwrap<VenueData>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Level;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::VenueData^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapVenueData(::Windows::Devices::Geolocation::VenueData^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::VenueData^ UnwrapVenueData(Local<Value> value);
  };
  Persistent<FunctionTemplate> VenueData::s_constructorTemplate;

  v8::Local<v8::Value> WrapVenueData(::Windows::Devices::Geolocation::VenueData^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VenueData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::VenueData^ UnwrapVenueData(Local<Value> value)
  {
     return VenueData::Unwrap<VenueData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVenueData(Local<Object> exports)
  {
    VenueData::Init(exports);
  }

  class Geocoordinate : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Geocoordinate").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("accuracy").ToLocalChecked(), AccuracyGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitude").ToLocalChecked(), AltitudeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitudeAccuracy").ToLocalChecked(), AltitudeAccuracyGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("heading").ToLocalChecked(), HeadingGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("latitude").ToLocalChecked(), LatitudeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("longitude").ToLocalChecked(), LongitudeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("speed").ToLocalChecked(), SpeedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timestamp").ToLocalChecked(), TimestampGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("point").ToLocalChecked(), PointGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("positionSource").ToLocalChecked(), PositionSourceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("satelliteData").ToLocalChecked(), SatelliteDataGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("positionSourceTimestamp").ToLocalChecked(), PositionSourceTimestampGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("Geocoordinate").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Geocoordinate(::Windows::Devices::Geolocation::Geocoordinate^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::Geocoordinate^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::Geocoordinate^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Geocoordinate *wrapperInstance = new Geocoordinate(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void AccuracyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        double result = wrapper->_instance->Accuracy;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AltitudeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->Altitude;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AltitudeAccuracyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->AltitudeAccuracy;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeadingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->Heading;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LatitudeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        double result = wrapper->_instance->Latitude;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LongitudeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        double result = wrapper->_instance->Longitude;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SpeedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Platform::IBox<double>^ result = wrapper->_instance->Speed;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimestampGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->Timestamp;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PointGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::Geopoint^ result = wrapper->_instance->Point;
        info.GetReturnValue().Set(WrapGeopoint(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionSourceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::PositionSource result = wrapper->_instance->PositionSource;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SatelliteDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::GeocoordinateSatelliteData^ result = wrapper->_instance->SatelliteData;
        info.GetReturnValue().Set(WrapGeocoordinateSatelliteData(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PositionSourceTimestampGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocoordinate^>(info.This()))
      {
        return;
      }

      Geocoordinate *wrapper = Geocoordinate::Unwrap<Geocoordinate>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->PositionSourceTimestamp;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::Geocoordinate^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeocoordinate(::Windows::Devices::Geolocation::Geocoordinate^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::Geocoordinate^ UnwrapGeocoordinate(Local<Value> value);
  };
  Persistent<FunctionTemplate> Geocoordinate::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeocoordinate(::Windows::Devices::Geolocation::Geocoordinate^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Geocoordinate::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::Geocoordinate^ UnwrapGeocoordinate(Local<Value> value)
  {
     return Geocoordinate::Unwrap<Geocoordinate>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeocoordinate(Local<Object> exports)
  {
    Geocoordinate::Init(exports);
  }

  class CivicAddress : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("CivicAddress").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("city").ToLocalChecked(), CityGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("country").ToLocalChecked(), CountryGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("postalCode").ToLocalChecked(), PostalCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timestamp").ToLocalChecked(), TimestampGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("CivicAddress").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    CivicAddress(::Windows::Devices::Geolocation::CivicAddress^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::CivicAddress^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::CivicAddress^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::CivicAddress^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CivicAddress *wrapperInstance = new CivicAddress(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void CityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::CivicAddress^>(info.This()))
      {
        return;
      }

      CivicAddress *wrapper = CivicAddress::Unwrap<CivicAddress>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->City;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CountryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::CivicAddress^>(info.This()))
      {
        return;
      }

      CivicAddress *wrapper = CivicAddress::Unwrap<CivicAddress>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Country;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PostalCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::CivicAddress^>(info.This()))
      {
        return;
      }

      CivicAddress *wrapper = CivicAddress::Unwrap<CivicAddress>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->PostalCode;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::CivicAddress^>(info.This()))
      {
        return;
      }

      CivicAddress *wrapper = CivicAddress::Unwrap<CivicAddress>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->State;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TimestampGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::CivicAddress^>(info.This()))
      {
        return;
      }

      CivicAddress *wrapper = CivicAddress::Unwrap<CivicAddress>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->Timestamp;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::CivicAddress^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapCivicAddress(::Windows::Devices::Geolocation::CivicAddress^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::CivicAddress^ UnwrapCivicAddress(Local<Value> value);
  };
  Persistent<FunctionTemplate> CivicAddress::s_constructorTemplate;

  v8::Local<v8::Value> WrapCivicAddress(::Windows::Devices::Geolocation::CivicAddress^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CivicAddress::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::CivicAddress^ UnwrapCivicAddress(Local<Value> value)
  {
     return CivicAddress::Unwrap<CivicAddress>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCivicAddress(Local<Object> exports)
  {
    CivicAddress::Init(exports);
  }

  class Geoposition : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Geoposition").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("civicAddress").ToLocalChecked(), CivicAddressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("coordinate").ToLocalChecked(), CoordinateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("venueData").ToLocalChecked(), VenueDataGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("Geoposition").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Geoposition(::Windows::Devices::Geolocation::Geoposition^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::Geoposition^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geoposition^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::Geoposition^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Geoposition *wrapperInstance = new Geoposition(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void CivicAddressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geoposition^>(info.This()))
      {
        return;
      }

      Geoposition *wrapper = Geoposition::Unwrap<Geoposition>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::CivicAddress^ result = wrapper->_instance->CivicAddress;
        info.GetReturnValue().Set(WrapCivicAddress(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CoordinateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geoposition^>(info.This()))
      {
        return;
      }

      Geoposition *wrapper = Geoposition::Unwrap<Geoposition>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::Geocoordinate^ result = wrapper->_instance->Coordinate;
        info.GetReturnValue().Set(WrapGeocoordinate(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void VenueDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geoposition^>(info.This()))
      {
        return;
      }

      Geoposition *wrapper = Geoposition::Unwrap<Geoposition>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::VenueData^ result = wrapper->_instance->VenueData;
        info.GetReturnValue().Set(WrapVenueData(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::Geoposition^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeoposition(::Windows::Devices::Geolocation::Geoposition^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::Geoposition^ UnwrapGeoposition(Local<Value> value);
  };
  Persistent<FunctionTemplate> Geoposition::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeoposition(::Windows::Devices::Geolocation::Geoposition^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Geoposition::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::Geoposition^ UnwrapGeoposition(Local<Value> value)
  {
     return Geoposition::Unwrap<Geoposition>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeoposition(Local<Object> exports)
  {
    Geoposition::Init(exports);
  }

  class PositionChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PositionChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("PositionChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PositionChangedEventArgs(::Windows::Devices::Geolocation::PositionChangedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::PositionChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::PositionChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::PositionChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PositionChangedEventArgs *wrapperInstance = new PositionChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::PositionChangedEventArgs^>(info.This()))
      {
        return;
      }

      PositionChangedEventArgs *wrapper = PositionChangedEventArgs::Unwrap<PositionChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::Geoposition^ result = wrapper->_instance->Position;
        info.GetReturnValue().Set(WrapGeoposition(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::PositionChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPositionChangedEventArgs(::Windows::Devices::Geolocation::PositionChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::PositionChangedEventArgs^ UnwrapPositionChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PositionChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPositionChangedEventArgs(::Windows::Devices::Geolocation::PositionChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PositionChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::PositionChangedEventArgs^ UnwrapPositionChangedEventArgs(Local<Value> value)
  {
     return PositionChangedEventArgs::Unwrap<PositionChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPositionChangedEventArgs(Local<Object> exports)
  {
    PositionChangedEventArgs::Init(exports);
  }

  class StatusChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("StatusChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("StatusChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    StatusChangedEventArgs(::Windows::Devices::Geolocation::StatusChangedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::StatusChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::StatusChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::StatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StatusChangedEventArgs *wrapperInstance = new StatusChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::StatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      StatusChangedEventArgs *wrapper = StatusChangedEventArgs::Unwrap<StatusChangedEventArgs>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::PositionStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::StatusChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapStatusChangedEventArgs(::Windows::Devices::Geolocation::StatusChangedEventArgs^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::StatusChangedEventArgs^ UnwrapStatusChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> StatusChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapStatusChangedEventArgs(::Windows::Devices::Geolocation::StatusChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StatusChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::StatusChangedEventArgs^ UnwrapStatusChangedEventArgs(Local<Value> value)
  {
     return StatusChangedEventArgs::Unwrap<StatusChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStatusChangedEventArgs(Local<Object> exports)
  {
    StatusChangedEventArgs::Init(exports);
  }

  class Geolocator : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Geolocator").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "allowFallbackToConsentlessPositions", AllowFallbackToConsentlessPositions);
      
            
      Nan::SetPrototypeMethod(localRef, "getGeopositionAsync", GetGeopositionAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("reportInterval").ToLocalChecked(), ReportIntervalGetter, ReportIntervalSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("movementThreshold").ToLocalChecked(), MovementThresholdGetter, MovementThresholdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("desiredAccuracy").ToLocalChecked(), DesiredAccuracyGetter, DesiredAccuracySetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("locationStatus").ToLocalChecked(), LocationStatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("desiredAccuracyInMeters").ToLocalChecked(), DesiredAccuracyInMetersGetter, DesiredAccuracyInMetersSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(RequestAccessAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("requestAccessAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetGeopositionHistoryAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("getGeopositionHistoryAsync").ToLocalChecked(), func);
      Nan::SetAccessor(constructor, Nan::New<String>("defaultGeoposition").ToLocalChecked(), DefaultGeopositionGetter, DefaultGeopositionSetter);
      Nan::SetAccessor(constructor, Nan::New<String>("isDefaultGeopositionRecommended").ToLocalChecked(), IsDefaultGeopositionRecommendedGetter);

      Nan::Set(exports, Nan::New<String>("Geolocator").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Geolocator(::Windows::Devices::Geolocation::Geolocator^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::Geolocator^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::Geolocator^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geolocator();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Geolocator *wrapperInstance = new Geolocator(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


    static void GetGeopositionAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Geolocation::Geoposition^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetGeopositionAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsNumber()
        && info[1]->IsNumber())
      {
        try
        {
          ::Windows::Foundation::TimeSpan arg0 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[0]).FromMaybe(0));
          ::Windows::Foundation::TimeSpan arg1 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetGeopositionAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Devices::Geolocation::Geoposition^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = WrapGeoposition(result);
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};

            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void AllowFallbackToConsentlessPositions(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->AllowFallbackToConsentlessPositions();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void RequestAccessAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Devices::Geolocation::GeolocationAccessStatus>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::Devices::Geolocation::Geolocator::RequestAccessAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Devices::Geolocation::GeolocationAccessStatus> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = Nan::New<Integer>(static_cast<int>(result));
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};

            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetGeopositionHistoryAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Geolocation::Geoposition^>^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          
          op = ::Windows::Devices::Geolocation::Geolocator::GetGeopositionHistoryAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsDate()
        && info[1]->IsNumber())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          ::Windows::Foundation::TimeSpan arg1 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[1]).FromMaybe(0));
          
          op = ::Windows::Devices::Geolocation::Geolocator::GetGeopositionHistoryAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Devices::Geolocation::Geoposition^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            TryCatch tryCatch;
            Local<Value> error; 
            Local<Value> arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Devices::Geolocation::Geoposition^>::CreateVectorViewWrapper(result, 
            [](::Windows::Devices::Geolocation::Geoposition^ val) -> Local<Value> {
              return WrapGeoposition(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geoposition^>(value);
            },
            [](Local<Value> value) -> ::Windows::Devices::Geolocation::Geoposition^ {
              return UnwrapGeoposition(value);
            }
          );
            if (tryCatch.HasCaught())
            {
              error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
            }
            else 
            {
              error = Undefined();
            }
            if (arg1.IsEmpty()) arg1 = Undefined();
            Local<Value> args[] = {error, arg1};

            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }


    static void ReportIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->ReportInterval;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ReportIntervalSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsUint32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        
        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->ReportInterval = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void MovementThresholdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        double result = wrapper->_instance->MovementThreshold;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MovementThresholdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsNumber())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        
        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->MovementThreshold = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DesiredAccuracyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::PositionAccuracy result = wrapper->_instance->DesiredAccuracy;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DesiredAccuracySetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        
        ::Windows::Devices::Geolocation::PositionAccuracy winRtValue = static_cast<::Windows::Devices::Geolocation::PositionAccuracy>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->DesiredAccuracy = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void LocationStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::PositionStatus result = wrapper->_instance->LocationStatus;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DesiredAccuracyInMetersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        ::Platform::IBox<unsigned int>^ result = wrapper->_instance->DesiredAccuracyInMeters;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DesiredAccuracyInMetersSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsUint32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
      {
        return;
      }

      Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());

      try 
      {
        
        ::Platform::IBox<unsigned int>^ winRtValue = ref new ::Platform::Box<unsigned int>(static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0)));

        wrapper->_instance->DesiredAccuracyInMeters = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    

    static void DefaultGeopositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Platform::IBox<::Windows::Devices::Geolocation::BasicGeoposition>^ result = ::Windows::Devices::Geolocation::Geolocator::DefaultGeoposition;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(BasicGeopositionToJsObject(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DefaultGeopositionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!IsBasicGeopositionJsObject(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      try 
      {

        
        ::Platform::IBox<::Windows::Devices::Geolocation::BasicGeoposition>^ winRtValue = ref new ::Platform::Box<::Windows::Devices::Geolocation::BasicGeoposition>(BasicGeopositionFromJsObject(value));

        ::Windows::Devices::Geolocation::Geolocator::DefaultGeoposition = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IsDefaultGeopositionRecommendedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        bool result = ::Windows::Devices::Geolocation::Geolocator::IsDefaultGeopositionRecommended;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
		return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PositionChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Geolocation::Geolocator^, ::Windows::Devices::Geolocation::PositionChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Geolocation::Geolocator^ arg0, ::Windows::Devices::Geolocation::PositionChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = WrapGeolocator(arg0);
                Local<Value> wrappedArg1 = WrapPositionChangedEventArgs(arg1);

                if (tryCatch.HasCaught())
                {
                  error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
                }
                else 
                {
                  error = Undefined();
                }


                if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->StatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Devices::Geolocation::Geolocator^, ::Windows::Devices::Geolocation::StatusChangedEventArgs^>(
            [callbackObjPtr](::Windows::Devices::Geolocation::Geolocator^ arg0, ::Windows::Devices::Geolocation::StatusChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = WrapGeolocator(arg0);
                Local<Value> wrappedArg1 = WrapStatusChangedEventArgs(arg1);

                if (tryCatch.HasCaught())
                {
                  error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
                }
                else 
                {
                  error = Undefined();
                }


                if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else 
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
		return;
      }

      Local<Object> tokenMap = Nan::To<Object>(NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked())).ToLocalChecked();
                
      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap,Undefined()).FromMaybe(false))
      {
		  tokenMap = Nan::New<Object>();
		  NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      }

      Nan::Set(tokenMap, info[1], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str)) &&(NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
                
      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false))
      {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[1]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false))
      {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());
            
      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;
        
      try 
      {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());
          wrapper->_instance->PositionChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geolocator^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          Geolocator *wrapper = Geolocator::Unwrap<Geolocator>(info.This());
          wrapper->_instance->StatusChanged::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::Devices::Geolocation::Geolocator^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeolocator(::Windows::Devices::Geolocation::Geolocator^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::Geolocator^ UnwrapGeolocator(Local<Value> value);
  };
  Persistent<FunctionTemplate> Geolocator::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeolocator(::Windows::Devices::Geolocation::Geolocator^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Geolocator::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::Geolocator^ UnwrapGeolocator(Local<Value> value)
  {
     return Geolocator::Unwrap<Geolocator>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeolocator(Local<Object> exports)
  {
    Geolocator::Init(exports);
  }

  class Geocircle : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Geocircle").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("center").ToLocalChecked(), CenterGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("radius").ToLocalChecked(), RadiusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("altitudeReferenceSystem").ToLocalChecked(), AltitudeReferenceSystemGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("geoshapeType").ToLocalChecked(), GeoshapeTypeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("spatialReferenceId").ToLocalChecked(), SpatialReferenceIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("Geocircle").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Geocircle(::Windows::Devices::Geolocation::Geocircle^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
	    	  return;
        }
        else
        {
          info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr).ToLocalChecked());
		       return;
        }
      }
      
      ::Windows::Devices::Geolocation::Geocircle^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocircle^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::Devices::Geolocation::Geocircle^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && IsBasicGeopositionJsObject(info[0])
        && info[1]->IsNumber())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          double arg1 = Nan::To<double>(info[1]).FromMaybe(0.0);
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geocircle(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && IsBasicGeopositionJsObject(info[0])
        && info[1]->IsNumber()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          double arg1 = Nan::To<double>(info[1]).FromMaybe(0.0);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg2 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geocircle(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && IsBasicGeopositionJsObject(info[0])
        && info[1]->IsNumber()
        && info[2]->IsInt32()
        && info[3]->IsUint32())
      {
        try
        {
          ::Windows::Devices::Geolocation::BasicGeoposition arg0 = BasicGeopositionFromJsObject(info[0]);
          double arg1 = Nan::To<double>(info[1]).FromMaybe(0.0);
          ::Windows::Devices::Geolocation::AltitudeReferenceSystem arg2 = static_cast<::Windows::Devices::Geolocation::AltitudeReferenceSystem>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          unsigned int arg3 = static_cast<unsigned int>(Nan::To<uint32_t>(info[3]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Devices::Geolocation::Geocircle(arg0,arg1,arg2,arg3);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Geocircle *wrapperInstance = new Geocircle(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void CenterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocircle^>(info.This()))
      {
        return;
      }

      Geocircle *wrapper = Geocircle::Unwrap<Geocircle>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::BasicGeoposition result = wrapper->_instance->Center;
        info.GetReturnValue().Set(BasicGeopositionToJsObject(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RadiusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocircle^>(info.This()))
      {
        return;
      }

      Geocircle *wrapper = Geocircle::Unwrap<Geocircle>(info.This());

      try 
      {
        double result = wrapper->_instance->Radius;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AltitudeReferenceSystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocircle^>(info.This()))
      {
        return;
      }

      Geocircle *wrapper = Geocircle::Unwrap<Geocircle>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::AltitudeReferenceSystem result = wrapper->_instance->AltitudeReferenceSystem;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GeoshapeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocircle^>(info.This()))
      {
        return;
      }

      Geocircle *wrapper = Geocircle::Unwrap<Geocircle>(info.This());

      try 
      {
        ::Windows::Devices::Geolocation::GeoshapeType result = wrapper->_instance->GeoshapeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SpatialReferenceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Geolocation::Geocircle^>(info.This()))
      {
        return;
      }

      Geocircle *wrapper = Geocircle::Unwrap<Geocircle>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->SpatialReferenceId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::Devices::Geolocation::Geocircle^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapGeocircle(::Windows::Devices::Geolocation::Geocircle^ wintRtInstance);
    friend ::Windows::Devices::Geolocation::Geocircle^ UnwrapGeocircle(Local<Value> value);
  };
  Persistent<FunctionTemplate> Geocircle::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeocircle(::Windows::Devices::Geolocation::Geocircle^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Geocircle::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Devices::Geolocation::Geocircle^ UnwrapGeocircle(Local<Value> value)
  {
     return Geocircle::Unwrap<Geocircle>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeocircle(Local<Object> exports)
  {
    Geocircle::Init(exports);
  }

} } } } 

NAN_MODULE_INIT(init)
{
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  
  NodeRT::Windows::Devices::Geolocation::InitPositionAccuracyEnum(target);
  NodeRT::Windows::Devices::Geolocation::InitPositionStatusEnum(target);
  NodeRT::Windows::Devices::Geolocation::InitPositionSourceEnum(target);
  NodeRT::Windows::Devices::Geolocation::InitGeoshapeTypeEnum(target);
  NodeRT::Windows::Devices::Geolocation::InitAltitudeReferenceSystemEnum(target);
  NodeRT::Windows::Devices::Geolocation::InitGeolocationAccessStatusEnum(target);
  NodeRT::Windows::Devices::Geolocation::InitIGeoshape(target);
  NodeRT::Windows::Devices::Geolocation::InitGeopoint(target);
  NodeRT::Windows::Devices::Geolocation::InitGeopath(target);
  NodeRT::Windows::Devices::Geolocation::InitGeoboundingBox(target);
  NodeRT::Windows::Devices::Geolocation::InitGeocoordinateSatelliteData(target);
  NodeRT::Windows::Devices::Geolocation::InitVenueData(target);
  NodeRT::Windows::Devices::Geolocation::InitGeocoordinate(target);
  NodeRT::Windows::Devices::Geolocation::InitCivicAddress(target);
  NodeRT::Windows::Devices::Geolocation::InitGeoposition(target);
  NodeRT::Windows::Devices::Geolocation::InitPositionChangedEventArgs(target);
  NodeRT::Windows::Devices::Geolocation::InitStatusChangedEventArgs(target);
  NodeRT::Windows::Devices::Geolocation::InitGeolocator(target);
  NodeRT::Windows::Devices::Geolocation::InitGeocircle(target);

  NodeRT::Utils::RegisterNameSpace("Windows.Devices.Geolocation", target);
}


NODE_MODULE(binding, init)
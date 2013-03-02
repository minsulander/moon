#ifndef MOONET_SERIALIZEMACROS_H
#define MOONET_SERIALIZEMACROS_H

namespace moonet {
	
#define MOONET_PRECISION_LOW

#ifdef MOONET_USE_RAKNET
	// RakNet

#	define SERIALIZE(var) bitstream->Write(var)
#	define DESERIALIZE(var) bitstream->Read(var)
#	define SERIALIZEf(var) bitstream->Write((float)var)
#	define DESERIALIZEf(var) { float f; bitstream->Read(f); var = f; }
	
#	if defined(MOONET_PRECISION_LOW)
#		define SERIALIZE_Vector3(x,y,z) bitstream->WriteVector(x,y,z)
#		define DESERIALIZE_Vector3(x,y,z) bitstream->ReadVector(x,y,z)
#	else
#		define SERIALIZE_Vector3(x,y,z) \
			bitstream->Write((float)x);\
			bitstream->Write((float)y);\
			bitstream->Write((float)z)	
#		define DESERIALIZE_Vector3(x,y,z) \
			{\
				float fx, fy, fz;\
				bitstream->Read(fx);\
				bitstream->Read(fy);\
				bitstream->Read(fz);\
				x = fx; y = fy; z = fz;\
			}
#	endif
	
#	define SERIALIZE_Vec3(v) SERIALIZE_Vector3(v[0], v[1], v[2])
#	define DESERIALIZE_Vec3(v) DESERIALIZE_Vector3(v[0], v[1], v[2])
	
#	if defined(MOONET_PRECISION_LOW)
#		define SERIALIZE_NormQuat(x,y,z,w) bitstream->WriteNormQuat(x,y,z,w)
#		define DESERIALIZE_NormQuat(x,y,z,w) bitstream->ReadNormQuat(x,y,z,w)
#	else
#		define SERIALIZE_NormQuat(x,y,z,w) \
			bitstream->Write((float)x);\
			bitstream->Write((float)y);\
			bitstream->Write((float)z);\
			bitstream->Write((float)w)
#		define DESERIALIZE_NormQuat(x,y,z,w) \
			{\
				float fx, fy, fz, fw;\
				bitstream->Read(fx);\
				bitstream->Read(fy);\
				bitstream->Read(fz);\
				bitstream->Read(fw);\
				x = fx; y = fy; z = fz; w = fw;\
			}
#	endif
#	define SERIALIZE_NQuat(v) SERIALIZE_NormQuat(v[0], v[1], v[2], v[3])
#	define DESERIALIZE_NQuat(v) DESERIALIZE_NormQuat(v[0], v[1], v[2], v[3])
	
#	define SERIALIZE_Vector4(x,y,z,w) \
		bitstream->Write((float)x);\
		bitstream->Write((float)y);\
		bitstream->Write((float)z);\
		bitstream->Write((float)w)
#	define DESERIALIZE_Vector4(x,y,z,w) \
		{\
			float fx, fy, fz, fw;\
			bitstream->Read(fx);\
			bitstream->Read(fy);\
			bitstream->Read(fz);\
			bitstream->Read(fw);\
			x = fx; y = fy; z = fz; w = fw;\
		}
	
#	define SERIALIZE_Vec4(v) SERIALIZE_Vector4(v[0], v[1], v[2], v[3])
#	define DESERIALIZE_Vec4(v) DESERIALIZE_Vector4(v[0], v[1], v[2], v[3])

#	define SERIALIZE_String(str) StringCompressor::Instance()->EncodeString(str.c_str(), str.size()+1, bitstream)
#	define DESERIALIZE_String(str, maxsize) { char buf[maxsize]; StringCompressor::Instance()->DecodeString(buf, sizeof(buf), bitstream); str = buf; }

#	define SERIALIZE_1() bitstream->Write1()
#	define SERIALIZE_0() bitstream->Write0()
#	define SERIALIZE_Bit(var) if (var) bitstream->Write1(); else bitstream->Write0() 
#	define DESERIALIZE_Bit() bitstream->ReadBit()
	
#else
	// NoNet
#	define SERIALIZE(var)
#	define DESERIALIZE(var)
#	define SERIALIZEf(var)
#	define DESERIALIZEf(var) var = 0.0f
	
#	define SERIALIZE_Vector3(x,y,z)
#	define DESERIALIZE_Vector3(x,y,z) x = y = z = 0

#	define SERIALIZE_Vec3(v)
#	define DESERIALIZE_Vec3(v) v[0] = v[1] = v[2] = 0
		
#	define SERIALIZE_NQuat(v) 
#	define DESERIALIZE_NQuat(v) v[0] = v[1] = v[2] = v[3] = 0
#	define SERIALIZE_Vector4(x,y,z,w)
#	define DESERIALZE_Vector4(x,y,z,w) x = y = z = w = 0

#	define SERIALIZE_String(str)
#	define DESERIALIZE_String(str, maxsize) str = ""

#	define SERIALIZE_1()
#	define SERIALIZE_0()
#	define SERIALIZE_Bit(b)
#	define DESERIALIZE_Bit() false

#endif
	
}

#endif

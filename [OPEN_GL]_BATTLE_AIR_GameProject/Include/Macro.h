#pragma once


// ============================================
// 매크로 함수를 관리합니다. 
// ============================================


#define SAFE_DELETE(p)		 if(p){ delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p  = NULL;}
#define SAFE_RELEASE(p)	if(p)	{p->Release(); p = NULL;}

// 싱글톤을 선언합니다. 
#define DECLARE_SINGLE(Type)\
private:\
	static Type* m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

// 싱글톤을 외부에서 선언합니다. 
#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL;
// 싱글톤을 얻습니다. ( 외부에서 사용 )
#define GET_SINGLE(Type) Type::GetInst()
// 싱글톤을 제거합니다. 
#define DESTROY_SINGLE(Type) Type::DestroyInst()

#define GETRESOLUTION CCore::GetInst()->GetResolution()

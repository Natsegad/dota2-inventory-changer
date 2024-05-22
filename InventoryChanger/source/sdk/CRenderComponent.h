#include <Windows.h>

class CRenderComponent {
public:
	CRenderComponent(void* ptr): m_pRenderCompPtr(ptr){}
	void SetRenderEnable(const bool& value);
	bool GetRenderEnable();
private:
	void* m_pRenderCompPtr;
};
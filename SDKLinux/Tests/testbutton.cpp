#include "testbutton.h"

TestButton::TestButton()
{
}

TestButton::~TestButton()
{
}

int TestButton::Perform()
{
	class VentanaInicio : public XWindow {
		ControlButton *buttonClose;
		ControlButton *buttonTest1;
	protected:
		virtual void Prepare() {
			buttonClose = new ControlButton("Close", NPoint(10, 10));
			buttonTest1 = new ControlButton("Test 1", NRectangle(10, 30, 50, 20));
			ControlAdd(buttonClose);
			ControlAdd(buttonTest1);
		}
		
		virtual void Destroy() {
			ControlRemove(buttonClose);
			ControlRemove(buttonTest1);
			delete buttonClose;
			delete buttonTest1;
		}
		
	public:
		VentanaInicio(const XDisplay &d) : XWindow(d) {}
		
	};
	
	XDisplay d;
	VentanaInicio v(d);
	v.RunModal();
	
	return 0;
}


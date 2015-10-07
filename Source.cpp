
#include "Application.h"
using namespace nsfw;

void main()
{
	Application d;

	d.init(800,600);
	d.play();
	d.term();

	system("pause");
}
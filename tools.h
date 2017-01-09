/** UTILITIES **/

#ifndef __TOOLS__
#define __TOOLS__

#include "constantes.h"

void SetColor(int ForgC);
sf::Color getColorByName(string colorname);
string getNameByColor(const sf::Color);
void debug(string text);
string sizeToString(size_t sz);

#endif // __TOOLS__

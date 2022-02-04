#include <string>
#include <vector>
using namespace std;
vector<string> modTry;
void exModUrlFind(string modid, string const moddn) {

	if (moddn.find(" ") != -1) { 
		string moddisplayname = moddn;
		string tt;
		string ttt = "";
		istringstream ist(moddisplayname);
		while (getline(ist, tt, ' ')) ttt += tt[0];
		modTry.push_back(ttt);

		while(moddisplayname.find(" ") != -1) moddisplayname.replace(moddisplayname.find(" "), string(" ").size(), "-");
		for (size_t i = 0; i < moddisplayname.size(); i++) moddisplayname[i] = tolower(moddisplayname[i]);
		for (size_t i = 0; i < moddisplayname.size(); i++)
		{
			if ((moddisplayname[i] < 'a' || moddisplayname[i] > 'z') && moddisplayname[i] != '-') {
				moddisplayname.erase(i, 1);
				i -= 1;
			}
		}
		modTry.push_back(moddisplayname); 
	}



}
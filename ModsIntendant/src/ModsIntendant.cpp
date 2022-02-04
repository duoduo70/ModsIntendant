#pragma warning(disable:6031 26478 26451 26495 26439 26819)

#include "../library/httplib/httplib.h"
#include "../library/zlib+minizip/MyMiniZip.h"
#include "../library/configor/json.hpp"
//#include <iostream>      httplib included
//#include <string>        httplib included
//#include <map>           httplib included
//#include <vector>        httplib included
//#include <fstream>       httplib included
#include <filesystem>
#include <urlmon.h>
#include<algorithm>
#include <codecvt>
#include "ExModUrlFind.hpp"

//#define COMPILE_EXTRA_MOUDLE

#pragma comment(lib, "urlmon.lib")

#define or else if
using namespace std;
using namespace configor;
//vector<string> modTry;

namespace Put
{
#define INFO "INFO"
#define WARN "WARNING"
#define ERR "ERROR"
#define FATAL "FATAL"
#define FATAL_P "FATAL+"

#define EFFECT_NONE "\033[0m"
#define EFFECT_BLACK "\033[0;30m"
#define EFFECT_DARK_GRAY "\033[1;30m"
#define EFFECT_BLUE "\033[0;34m"
#define EFFECT_LIGHT_BLUE "\033[1;34m"
#define EFFECT_GREEN "\033[0;32m"
#define EFFECT_LIGHT_GREEN "\033[1;32m"
#define EFFECT_CYAN "\033[0;36m"
#define EFFECT_LIGHT_CYAN "\033[1;36m"
#define EFFECT_RED "\033[0;31m"
#define EFFECT_LIGHT_RED "\033[1;31m"
#define EFFECT_PURPLE "\033[0;35m"
#define EFFECT_LIGHT_PURPLE "\033[1;35m"
#define EFFECT_BROWN "\033[0;33m"
#define EFFECT_YELLOW "\033[1;33m"
#define EFFECT_LIGHT_GRAY "\033[0;37m"
#define EFFECT_WHITE "\033[1;37m"
	inline auto commandInput_line(std::string tip = "") {
		std::string line;
		std::cout << tip;
		std::getline(std::cin, line);
		return line;
	}
	auto(*_commin)(std::string) = &commandInput_line;
	inline auto commandInput(std::string tip = "") {
		std::string comm;
		std::cout << tip;
		std::cin >> comm;
		return comm;
	}
	auto(*commin)(std::string) = &commandInput;
	auto(*input)(std::string) = &commandInput;
	void putInfo(std::string info, std::string level = "INFO", std::string tip = "", std::string publisher = "STARTER") {
		time_t nowtime = time(0);
		tm ltm;
		localtime_s(&ltm, &nowtime);
		std::cout << ltm.tm_year + 1900 << ":" << ltm.tm_mon + 1 << ":" << ltm.tm_mday << ":" << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << " [" << level << "][" << publisher << "] " << info << ((tip != "") ? (" " + tip) : "") << std::endl;
	}
	auto(*pinfo)(std::string, std::string, std::string, std::string) = &putInfo;
	inline void putText(std::string text) {
		std::cout << "	" << text << std::endl;
	}
	auto(*put)(std::string) = &putText;
	inline void putExtraText(std::string text) {
		std::cout << text << std::endl;
	}
	void(*put_ex)(std::string) = &putExtraText;
	auto findEffect(std::string effect) {
		//if (effect == "NONE") effect = EFFECT_NONE;
		if (effect == "BLACK") effect = EFFECT_BLACK;
		if (effect == "DARK_GRAY") effect = EFFECT_DARK_GRAY;
		if (effect == "BLUE") effect = EFFECT_BLUE;
		if (effect == "LIGHT_BLUE") effect = EFFECT_LIGHT_BLUE;
		if (effect == "GREEN") effect = EFFECT_GREEN;
		if (effect == "LIGHT_GREEN") effect = EFFECT_LIGHT_GREEN;
		if (effect == "CYAN") effect = EFFECT_CYAN;
		if (effect == "LIGHT_CYAN") effect = EFFECT_LIGHT_CYAN;
		if (effect == "RED") effect = EFFECT_RED;
		if (effect == "LIGHT_RED") effect = EFFECT_LIGHT_RED;
		if (effect == "PURPLE") effect = EFFECT_PURPLE;
		if (effect == "LIGHT_PURPLE") effect = EFFECT_LIGHT_PURPLE;
		if (effect == "BROWN") effect = EFFECT_BROWN;
		if (effect == "YELLOW") effect = EFFECT_YELLOW;
		if (effect == "LIGHT_GRAY") effect = EFFECT_LIGHT_GRAY;
		if (effect == "WHITE") effect = EFFECT_WHITE;
		else effect = EFFECT_NONE;
		return effect;
	}
	void putEffectText(std::string text, std::string effect = "\033[0m")
	{
		std::cout << "	" << effect << text << "\033[0m" << std::endl;
	}
	auto effectInput(std::string effect = "\033[0m", std::string tip = "", std::string comminEff = "\033[0m")
	{
		std::string comm;
		std::cout << comminEff << tip << effect;
		std::cin >> comm;
		std::cout << "\033[0mm";
		return comm;
	}
}

namespace InNET {
	wstring getCurseforgeAPIW() {
		return L"api.cfwidget.com";
	}
	wstring getHTTPW() {
		return L"https://";
	}
	wstring getVirtualDirW(int mode = 0) {
		return L"/minecraft/mc-mods/";
	}
	wstring getPortW() {
		return L":80";
	}
	string getCurseforgeAPI(short version = 2) {
		if (version == 1) return "api.curseforge.com";
		return "api.cfwidget.com";
	}
	string getHTTP(short version = 2) {
		return "http://";
	}
	string getVirtualDir(short version = 2) {
		if (version == 1) return "/v1/mods/";
		return "/minecraft/mc-mods/";
	}
	string getPort(short version = 2) {
		return ":80";
	}
}
namespace StrCoding {
	
}
using namespace Put;
using namespace std::filesystem;
#define UD putExtraText("\033[0;31mUnder development\033[0m")
#define WIP putExtraText("\033[1;33mWIP\033[0m")
#define OK put_ex("\033[1;32msuccessful\033[0m")
#define FAIL put_ex("\033[0;31mWas Faild\033[0m");
namespace Mem {
	vector<path> filelist;
	path dirname;
	vector<path> modsnamelist;
	vector<path> modidlist;
	vector<path> moddnlist;
	bool isUnJAROK = false;
	string apikey = "";
	string version = "1.12.2";
}
namespace Command {
void comm_help() {
	UD;
}
void comm_dir(string dirstr) {
	path dirpath(dirstr);
	if (!exists(dirpath)) { throw dirpath; return; }
	Mem::dirname = dirpath;
	directory_entry direntry(dirstr);
	if (direntry.status().type() != file_type::directory) { throw dirstr; return; }
	directory_iterator dirlist(dirstr);
	vector<path> liststr;
	for (auto& it : dirlist) liststr.push_back(it.path().filename());
	WIP;
	throw liststr;
	throw dirpath;
}
void comm_list() {
	for (auto& i : Mem::filelist) cout << i << endl;
	WIP;
}
void _findMODS() {
	if (Mem::filelist.empty()) { put_ex("DirListIsEmpty"); return; }
	if (!exists(Mem::dirname/"mods")) { put_ex("CanNotFindDir:mods"); return; }
}
void comm_minecraftdir() {

}
void comm_mods_names() {
	_findMODS();
	Mem::modsnamelist.clear();
	for (auto& ele : directory_iterator(Mem::dirname/"mods")) Mem::modsnamelist.push_back(ele.path().filename());
	for (auto& element : Mem::modsnamelist) cout << element << endl;
	OK;
	WIP;
}
void _UnJARs() {
	Mem::modsnamelist.clear();
	for (auto& ele : directory_iterator(Mem::dirname / "mods")) Mem::modsnamelist.push_back(ele.path().filename());
	Mem::modidlist.clear();
	create_directory(Mem::dirname / "modparse.temp");
	int time = 0;
	vector<path> errorMOD;
	for (auto& element : Mem::modsnamelist) {
		MyMiniZip unZip;
		create_directory(Mem::dirname / "modparse.temp" / element.stem());
		if (!unZip.unZipPackageToLoacal((Mem::dirname / "mods" / element).string(), (Mem::dirname / "modparse.temp" / element.stem()).string())) {
			errorMOD.push_back(element);
			put_ex(element.filename().string() + ":UnFail");
			time += unZip.GetCountTime();
			continue;
		}
		put_ex(element.filename().string() + ":UnOK");
		time += unZip.GetCountTime();
	}
	put_ex("UnJARUnavailable:" + to_string(time) + "s");
	put_ex("UnJARQuantity:" + to_string(Mem::modsnamelist.size()));
	if (!errorMOD.empty()) for (auto& i : errorMOD) put_ex("UnFail:" + i.string());
	Mem::isUnJAROK = true;
	//OK;
	//WIP;
}
int _findNstPos(char* str, char c, int n) {
	char* p = str;
	int index = 0;
	int count = 0;
	while (*p != '\0') {
		if (*p == c) count++;
		if (count < n) {
			p++;
			index++;
		}
		else break;
	}
	return index;
}
//void comm_mods_modids() {
//	if (Mem::isUnJAROK == false) _UnJARs();
//	vector<string> errorMOD;
//	put_ex("\nMODID_LIST");
//	put_ex("----------------------------");
//	Mem::modidlist.clear();
//	for (auto& element : Mem::modsnamelist) {
//		ifstream moddir((Mem::dirname / "modparse.temp" / element.stem() / "mcmod.info").string());
//		if (!moddir.is_open()) { errorMOD.push_back(element.stem().string()); continue; }
//		string line;
//		while (getline(moddir, line)) {
//			if (strstr(line.c_str(), "modid") || strstr(line.c_str(), "name")) {
//				bool ismodid = strstr(line.c_str(), "modid");
//				//cout << line;
//				string modid = line.substr(_findNstPos(const_cast<char*>(line.c_str()), '"', 3) + 1);
//				modid.erase(modid.find_first_of("\""));
//				put(modid);
//				if (ismodid) Mem::modidlist.push_back(modid);
//				else Mem::moddnlist.push_back(modid);
//				if(Mem::modidlist.size() == Mem::moddnlist.size()) break;
//			}
//		}
//		moddir.close();
//	}
//	put_ex("----------------------------");
//	for (auto& mod : errorMOD) put(EFFECT_YELLOW + string("OpenFail:") + mod + EFFECT_NONE);
//	OK;
//	WIP;
//}

std::string censorStrWithOutSymbol(std::string& source)
{
	string sourceWithOutSymbol;

	int i = 0;
	while (source[i] != 0)
	{
		if (source[i] & 0x80 && source[i] & 0x40 && source[i] & 0x20)
		{
			int byteCount = 0;
			if (source[i] & 0x10) byteCount = 4;
			else byteCount = 3;
			for (int a = 0; a < byteCount; a++)
			{
				source.erase(i, 1);
				i++;
			}
		}
		else if (source[i] & 0x80 && source[i] & 0x40) i += 2;
		else i += 1;
	}
	return source;
}
void loadMCMODInfo() {
	if (Mem::isUnJAROK == false) _UnJARs();
	vector<string> errorMOD;
	put_ex("\nMODID_LIST");
	put_ex("----------------------------");
	Mem::modidlist.clear();
	Mem::moddnlist.clear();
	for (auto& element : Mem::modsnamelist) {
		ifstream moddir((Mem::dirname / "modparse.temp" / element.stem() / "mcmod.info").string());
		if (!moddir.is_open()) { errorMOD.push_back(element.stem().string()); continue; }
		string t_mcmodinfo = string((std::istreambuf_iterator<char>(moddir)), std::istreambuf_iterator<char>());
		//cout << string("{\"mods\":") + t_mcmodinfo + string("}");

		t_mcmodinfo.erase(remove(t_mcmodinfo.begin(), t_mcmodinfo.end(),'\n'), t_mcmodinfo.end());
		json t_json = json::parse(string("{\"mods\":") + t_mcmodinfo + string("}"));
		if (t_mcmodinfo.find("\"modList\"")!=t_mcmodinfo.npos) {
			Mem::modidlist.push_back(t_json["mods"]["modList"][0]["modid"]);
			Mem::moddnlist.push_back(t_json["mods"]["modList"][0]["modid"]);
			put(t_json["mods"]["modList"][0]["modid"]);
		}
		else {
			Mem::modidlist.push_back(t_json["mods"][0]["modid"]);
			Mem::moddnlist.push_back(t_json["mods"][0]["name"]);
			put(t_json["mods"][0]["modid"]);
		}
		//string line;
		//while (getline(moddir, line)) {
		//	if (strstr(line.c_str(), "modid") || strstr(line.c_str(), "name")) {
		//		bool ismodid = strstr(line.c_str(), "modid");
		//		//cout << line;
		//		string modid = line.substr(_findNstPos(const_cast<char*>(line.c_str()), '"', 3) + 1);
		//		modid.erase(modid.find_first_of("\""));
		//		put(modid);
		//		if (ismodid) Mem::modidlist.push_back(modid);
		//		else Mem::moddnlist.push_back(modid);
		//		if (Mem::modidlist.size() == Mem::moddnlist.size()) break;
		//	}
		//}
		moddir.close();
	}
	put_ex("----------------------------");
	for (auto& mod : errorMOD) put(EFFECT_YELLOW + string("OpenFail:") + mod + EFFECT_NONE);
	put_ex("");
	put_ex(string("Detected: ") + to_string(Mem::modidlist.size()) + string(" SingleMod"));
	OK;
	WIP;
}
void _mod_try(string mod,string displayname) {
	modTry.clear();
	modTry.push_back(mod);
	exModUrlFind(mod, displayname);
}
void comm_mods_checkforupdates_windows_old() {
	using namespace InNET;
	if (Mem::modidlist.empty()) loadMCMODInfo();
	vector<string> DownloadJSONFails;
	create_directory(Mem::dirname / "modparse.temp" / "curseforge-json");
	for (size_t i = 0; i < Mem::modidlist.size(); i++) {
		auto& modid = Mem::modidlist[i];
		_mod_try(modid.string(), Mem::moddnlist[i].string());
		for (auto& mod : modTry) {
			//TODO
			HRESULT hr = URLDownloadToFileW(nullptr, (getHTTPW() + getCurseforgeAPIW() + getVirtualDirW() + path(mod).wstring()).c_str(), (Mem::dirname / "modparse.temp" / "curseforge-json" / (modid.string() + ".json")).wstring().c_str(), 0, nullptr);
			if (hr != S_OK) {
				//TODO
				DownloadJSONFails.push_back(modid.string());
				remove(Mem::dirname / "modparse.temp" / "curseforge-json" / (modid.string() + ".json"));
			}
			else {
				put_ex("Download " + modid.string() + " ObjectJSON:OK");
				break;
			}
		}
	}
	put_ex("");
	for (auto& DownloadJSONFail : DownloadJSONFails) put_ex(EFFECT_YELLOW + string("DownloadMODObjectJSONFail: ") + DownloadJSONFail + " ByCurseForge" + EFFECT_NONE);
	put_ex("");
	int findUrlSurc = 0;
	vector<string> findUrlSuccessfulMod;
	directory_iterator dirlist(Mem::dirname / "modparse.temp" / "curseforge-json");
	vector<path> liststr;
	vector<string> sucmod;
	vector<string> urllist;
	for (auto& it : dirlist) {
		ifstream fObjJSON((Mem::dirname / "modparse.temp" / "curseforge-json" / it.path().filename()).string());
		json objjson;
		fObjJSON >> objjson;
		for (auto& fileobj : objjson["files"]) {
			for (auto& version : fileobj["versions"]) if (version == Mem::version) {
				findUrlSuccessfulMod.push_back(path(it).stem().string());
				string url = fileobj["url"].as_string();
				int filetodownload = url.find_last_of("files") - string("files").size();
				url.erase(filetodownload, string("files").size());
				url.insert(filetodownload + 1, "/download");
				url.append("/file");
				urllist.push_back(url);
				put_ex(path(it).stem().string() + (string)" NewUrl: " + EFFECT_LIGHT_BLUE + url + EFFECT_NONE + (string)" In " + fileobj["uploaded_at"].as_string());
				sucmod.push_back(path(it).stem().string());
				goto LoopsOfNewFileUrlFindEnd;
			}
		}
	LoopsOfNewFileUrlFindEnd:findUrlSurc += 1;
	}
	for (auto& i : Mem::modidlist) if (find(sucmod.begin(), sucmod.end(), i.string()) == sucmod.end()) put_ex(EFFECT_YELLOW+string("CanNotFindUrl: ") + i.string()+EFFECT_NONE);
	put_ex(string("FindUrlSuccessfulMod: ") + to_string(findUrlSurc - 1));
	put_ex(string("DetectedModPercentage: ") + to_string((double)(findUrlSurc - 1) / Mem::modidlist.size() * 100) + "%");
	/*put_ex("");
	for (auto& mod : findUrlSuccessfulMod) {
		if (find(Mem::modidlist.begin(), Mem::modidlist.end(), path(mod)) != Mem::modidlist.end()) put_ex(string("Mod:CanNotFindUrl: ") + string(mod));
	}*/
	put_ex("");
	put_ex("YouMeyNeedToDoAHunManMachineVerificationIn https://www.curseforge.com OrStartVPNToCFWhitelistYourIP");
	put_ex("PreesAnyKeyToDownload IfYouDoNotWantToDo Input n");
	put_ex(EFFECT_YELLOW + string("[Y/n]") + EFFECT_NONE);
	string t_in;
	cin >> t_in;
	if (t_in != "n") {
		for (auto& url : urllist) {
			wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			if (URLDownloadToFileW(nullptr, converter.from_bytes(url).c_str(), (Mem::dirname / "mods").wstring().c_str(), 0, nullptr) == !S_OK) put_ex(EFFECT_RED + string("Fail: ") + url + EFFECT_NONE);
			else put_ex("DownloadMODOK:" + url);
		}
	}
	OK;
	WIP;
}
void comm_mods_checkforupdates_v1() {
	if (Mem::apikey == "") {
		put_ex(EFFECT_LIGHT_RED + (string)"CanNotFindAPI_KEY" + EFFECT_NONE);
		return;
	}
	using namespace InNET;
	if (Mem::modidlist.empty()) loadMCMODInfo();
	vector<string> DownloadJSONFails;
	create_directory(Mem::dirname / "modparse.temp" / "curseforge-json");
	const httplib::Headers getCFHeaders = {
			{"Accept","application/json"},
			{"x-zpi-key",Mem::apikey}
	};
	httplib::Client clientForCF((getHTTP(1) + getCurseforgeAPI(1) + getPort(1)));
	for (auto& modid : Mem::modidlist) {
		if (auto res = clientForCF.Get((getVirtualDir() + modid.string()).c_str(), getCFHeaders, [modid](uint64_t len, uint64_t total) {
			printf("%s: %lld / %lld bytes => %d%% complete\n", modid.string().c_str(), len, total, (int)(len * 100 / total));
			return true;
			})) {
			put_ex("Status:" + res->status);
			if (true) {
				std::ofstream out;
				out.open((Mem::dirname / "modparse.temp" / "curseforge-json" / modid).string() + ".json", ios_base::binary | ios::out);
				if (out.is_open()) {
					out << res->body;
					out.close();
					put_ex(modid.string() + "DownloadJSONForCurseforgeOK");
				}
				else DownloadJSONFails.push_back(modid.string());
			}
		}
		else put_ex("UrlConnectError: " + (int)res.error());
	}
	for (auto& DownloadJSONFail : DownloadJSONFails) put_ex(EFFECT_LIGHT_RED + string("DownloadMODObjectJSONFail: ") + DownloadJSONFail + " ByCurseForge" + EFFECT_NONE);
	OK;
	WIP;
}
void comm_mods_checkforupdates() {
	using namespace InNET;
	if (Mem::modidlist.empty()) loadMCMODInfo();
	vector<string> DownloadJSONFails;
	create_directory(Mem::dirname / "modparse.temp" / "curseforge-json");
	httplib::Client clientForCF(getHTTP(2) + getCurseforgeAPI(2));
	for (auto& modid : Mem::modidlist) {
		if (auto res = clientForCF.Get((getVirtualDir(2) + modid.string()).c_str(), [modid](uint64_t len, uint64_t total) {
			printf("%s: %lld / %lld bytes => %d%% complete\n", modid.string().c_str(), len, total, (int)(len * 100 / total));
			return true;
			})) {
			cout << getHTTP(2) + getCurseforgeAPI(2) + getVirtualDir(2) + modid.string() << endl;
			put_ex("Status:" + res->status);
			if (res->status == 200) {
				std::ofstream out;
				out.open((Mem::dirname / "modparse.temp" / "curseforge-json" / modid).string() + ".json", ios_base::binary | ios::out);
				if (out.is_open()) {
					out << res->body;
					out.close();
					put_ex(modid.string() + "DownloadJSONForCurseforgeOK");
				}
				else DownloadJSONFails.push_back(modid.string());
			}
		}
		else put_ex("UrlConnectError: " + (int)res.error());
	}
	for (auto& DownloadJSONFail : DownloadJSONFails) put_ex(EFFECT_LIGHT_RED + string("DownloadMODObjectJSONFail: ") + DownloadJSONFail + " ByCurseForge" + EFFECT_NONE);
	
	OK;
	WIP;
}
void getAPI_KEY(string api_key) {
	Mem::apikey = api_key;
}
void setMC_VERSION(string version) {
	Mem::version = version;
}

void canNotFindCommand(string comm) {put_ex("CanNotFindCommand:"+comm);}
}

using namespace Command;
namespace InRun
{
namespace CommandWhile
{
void CommandWhile() {
while (true)
{
string comm = commandInput("");
if (comm == "exit") break;
or (comm == "help") comm_help();
or (comm == "dir") {
	string commDir;
	cin >> commDir;
	try { comm_dir(commDir); }
	catch (string errdir) { Put::putExtraText(errdir + ":NotFind,OrThisIsNotADir"); }
	catch (vector<filesystem::path> dirpaths) { Mem::filelist = dirpaths; }
	catch (path dirpath) { cout << "CanNotFind:" << dirpath; }
}
or (comm == "list") comm_list();
or (comm == "mods") {
	string subcomm;
	cin >> subcomm;
	if (subcomm == "-names") comm_mods_names();
	else if (subcomm == "-modids") loadMCMODInfo();
	else if (subcomm == "-checkforupdates.windows.old") comm_mods_checkforupdates_windows_old();
	else if (subcomm == "-checkforupdates.v1") comm_mods_checkforupdates_v1();
	else if (subcomm == "-checkforupdates") comm_mods_checkforupdates();
	else Put::put_ex("CanNotFindSubCommand:"+subcomm);
}
or (comm == "-curseforge") {
	string subcomm;
	cin >> subcomm;
	if (subcomm == "apikey") {
		string apikey;
		cin >> apikey;
		getAPI_KEY(apikey);
	}
	else Put::put_ex("CanNotFindSubCommand:" + subcomm);
}
or (comm == "minecraftversion" || comm == "mcversion") {
	string version;
	cin >> version;
	setMC_VERSION(version);
}
or (comm == "-minecraftdir") {
	comm_minecraftdir();
}
or (comm == "-ex.unjarok") {
	Mem::isUnJAROK = true;
}

else canNotFindCommand(comm);
}//main while
}//CommandWhile::CommandWhile
}//CommandWhile
}//Run

int main()
{
	try
	{
		InRun::CommandWhile::CommandWhile();
	}
	catch (const std::exception&)
	{

	}
}
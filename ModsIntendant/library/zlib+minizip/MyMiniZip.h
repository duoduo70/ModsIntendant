#ifndef __MYMINIZIP__
#define __MYMINIZIP__
/*
@ ZLIB ʵ�ּ򵥵�zip�ļ�ѹ��|��ѹ������
@ ���� ZLIB
@ http://www.zlib.net/
@ 2018��12��17��
*/
#include <windows.h>
#include <string>
#include <chrono>
extern "C"
{
#include "zlib.h"
#include "zconf.h"
#include "unzip.h"
#include "zip.h"
}
/*
@ ��ȡ����ִ�к�ʱ������
*/
typedef std::chrono::system_clock::time_point Time;
class MyCTime
{
public:
	MyCTime();
	~MyCTime();
	Time start() const;
	Time end() const;
	int CountInterval(Time& begin, Time& end);
private:

};

/*
@ ������ ���� ѹ����ѹ�� 
*/
class MyMiniZip
{
public:
	explicit MyMiniZip();
	~MyMiniZip();
public:
	/*
	@ ��ȡunZipPackageToLoacal ������ѹ������ʱ
	*/
	int GetCountTime() const;
	/*
	@ ��ȡ��ǰ��ѹ�ļ�����ѹ���ļ���״̬��Ϣ
	*/
	std::string GetFileStatus() const;
	/*
	@ ��ȡѹ������ȫ��ע���ı�
	*/
	std::string GetGlobalComment() const;
	/*
	@ ѹ���ļ� �����ļ��� �ڲ��Զ��ж�
	@ strSourceFile Ҫ��ѹ�����ļ����ļ�·��ȫ��
	@ strSaveFile Ҫ���ɵ�zipѹ������ȫ·��
	@ ʧ�ܷ��� false �ɹ����� true
	*/
	bool CompressToPackageZip(const std::string strSourceFile, const std::string strSaveFile);
	/*
	@ ��ѹzip ���ļ���ָ��·��
	@ strSourceZipPath Ҫ����ѹ��zip�ļ���ȫ·��
	@ strDestZipPath ��Ҫ��ѹ���ı���·��
	@ �ɹ����� ��ѹ�ļ������� ʧ�ܷ��� null
	*/
	DWORD unZipPackageToLoacal(const std::string strSourceZipPath, const std::string strDestZipPath);
private:
	/*
	@ ���ļ������ļ�����ӵ�zipѹ������
	@ ZipFile zipFile ���
	@ strFileInZipName �ļ������ļ�������
	@ strPath ��� strPath Ϊnull��ʾ ���ļ��� �������ļ�
	*/
	bool addFileZip(zipFile ZipFile, const std::string strFileInZipName, const std::string strPath);
	/*
	 @ �ݹ�ʽ�����ļ����������ļ�����ӵ�zipѹ����
	 @ ZipFile zipFile ���
	 @ strFileInZipName �ļ������ļ�������
	 @ strPath ��� strPath Ϊnull��ʾ ���ļ��� �������ļ�
	*/
	bool  packFolderToZip(zipFile ZipFile, const std::string strFileInZipName, const std::string strPath);
	/*
	@ ѹ���ļ� �����ļ��� �ڲ��Զ��ж�
	@ strSourceFile Ҫ��ѹ�����ļ����ļ�·��ȫ��
	@ strSaveFile Ҫ���ɵ�zipѹ������ȫ·��
	@ nMode ��ʾѹ���ļ������ļ��� 0 ���ļ� 1 ���ļ���
	@ ʧ�ܷ��� false �ɹ����� true
	*/
	bool CompressToPackageZip(const std::string strSourceFile, const std::string strSaveFile,int nMode);
	/*
	@ ��ָ��·����ȡ�������ļ�
	@ szFileName Ҫ��ȡ���ļ�ȫ·��
	@ pFileBuffer �������ն�ȡ�ļ����ڴ�buffer
	@ ���ض�ȡ���ļ����ֽڴ�С ʧ�ܷ���null
	*/
	DWORD ReadFileBuffer(std::string szFileName, PVOID* pFileBuffer);
	/*
	@ ���ڴ���д�ļ����ݵ�����
	@ szFileNmae д���ļ���ȫ·��
	@ pFileBuffer д���ļ�������ָ��
	@ dwFileSize ��д���ļ��Ĵ�С����
	@ ʧ�ܷ��� -1 �ɹ� ����ʵ��д���ļ���С
	*/
	DWORD WriteFileBuffer(std::string szFileNmae, PVOID pFileBuffer, DWORD dwFileSize);
private:
	Time TimeBegin;
	Time TimeEnd;
	int nCountTime;
	/*
	@ ��ǰ������ѹ�ļ�״̬
	*/
	std::string file_status;
	/*
	@ ѹ������ȫ��ע���ı�
	*/
	std::string global_comment;
	/*
	@ ��ѹZIP���� ���
	*/
	unzFile unZipFileHandle;
};

#endif
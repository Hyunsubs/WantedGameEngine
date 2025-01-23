#pragma once
#include <iostream>
#include <windows.h>


class ENGINE_API Util
{
public:
    static std::string LoadFileContent(const char* filename)
    {
        std::string result;
        FILE* file = nullptr;
        // ���� ����
        fopen_s(&file, filename, "rt");
        if (!file) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return result;
        }

        // ���� ũ�� �˾Ƴ���
        fseek(file, 0, SEEK_END); // ���� ������ �̵�
        long fileSize = ftell(file); // ���� ũ�� ��������
        fseek(file, 0, SEEK_SET); // ���� ó������ �̵�

        // ���� ������ ������ ���� �Ҵ�
        char* buffer = (char*)malloc(fileSize + 1);
        if (!buffer) {
            std::cerr << "Memory allocation failed." << std::endl;
            fclose(file);
            return result;
        }

        // ���� ���� �б�
        fread(buffer, 1, fileSize + 1, file);
        buffer[fileSize] = '\0'; // null-terminator �߰�

        result += buffer;


        // �޸� ���� �� ���� �ݱ�
        free(buffer);
        fclose(file);

        return result;
    }
};



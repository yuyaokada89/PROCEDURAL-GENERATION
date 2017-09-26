#include "Obj3d.h"


#include <vector>

#pragma once


class RandomMapMaker
{
private:
	//�@�V�[�h�l
	float seedX;
	float seedZ;

	//�@�}�b�v�̃T�C�Y
	float width;
	float depth;

	//�@�����̍ő�l
	int MaxHeight;

	//�@�N���̌�����
	float relif;

	//�@�}�b�v�̃T�C�Y
	float MapSize;

	// �����f��
	std::vector<Obj3d>	m_cube;

public:
	//�@������
	RandomMapMaker();

	void SetY(float y);

	void Draw();

	
};

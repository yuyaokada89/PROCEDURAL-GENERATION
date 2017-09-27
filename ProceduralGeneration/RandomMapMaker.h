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
	int width;
	int depth;


	//�@�����̍ő�l
	int MaxHeight;

	//�@�N���̌�����
	float relif;

	// �����f��
	std::vector<Obj3d>	m_cube;

public:
	//�@������
	RandomMapMaker();

	void MakeY(int number);

	// ������
	void Initialize();

	//�@�X�V����
	void Update();

	//�@�s��X�V
	void Calc();

	//�@�`��
	void Draw();

};

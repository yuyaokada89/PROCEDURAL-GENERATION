#include "Obj3d.h"
#include "PerlinNoise.hpp"

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

	int RandomHeighit;

	int y;

	//�@�N���̌�����
	float relief;

	// �����f��
	std::vector<Obj3d>	m_cube;

	siv::PerlinNoise m_noise;

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

#include "Obj3d.h"
#include "PerlinNoise.hpp"
#include "VertexCube.h"

#include <vector>


#pragma once


class RandomMapMaker
{
public:


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

	std::vector<std::unique_ptr<VertexCube>> m_VertexCube;

public:
	//�@������
	RandomMapMaker();

	float MakeY(int x, int z);

	// ������
	void Initialize();

	//�@�X�V����
	void Update();

	//�@�s��X�V
	void Calc();

	//�@�`��
	void Draw();

};

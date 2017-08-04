#include "CudaParallel.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cstdio>
//#define _USE_MATH_DEFINES
#include <cmath>
#include "Type.h"

//ʹ��GPU���� �˺���
__global__ void CudaCaculateKernal(double* pX,double* pY,int nLength)
{
	if (nullptr == pX || nullptr == pY)
	{
		return;
	}
	//blockDim �߳̿��е��߳���
	//gridDim �����е��߳̿���
	//threadidx �߳̿��е��߳�����
	//blockidx �߳̿��������е�����
	int nIndex = blockDim.x * blockIdx.x + threadIdx.x;


	if (nIndex < 0 || nIndex >= nLength)
	{
		return;
	}

	pY[nIndex] = sin(pX[nIndex]);
	printf("nIndex = %d.\n", nIndex);

}

//����Cuda���в��м���ĺ���
void CalculateSinValue(int nLength)
{
	//�������ڴ��е����ݿ������豸�ڴ���
	//�����й�����
	double* pCudaX = NULL;
	double* pCudaY = NULL;

	//�й�����(���������豸�˶����Է���)
	cudaMallocManaged(&pCudaX, nLength * sizeof(double));
	cudaMallocManaged(&pCudaY, nLength * sizeof(double));

	double dStep = 2.0 * PI / nLength;

	for (int i = 0; i < nLength; ++i)
	{
		pCudaX[i] = i * dStep;
	}
	//�������м���������
	int n = (nLength + BLOCK_THREAD_NUM - 1) / BLOCK_THREAD_NUM;
	auto BlockSize = dim3(n, 1, 1);
	uint3 ThreadSize;
	ThreadSize.x = BLOCK_THREAD_NUM;
	ThreadSize.y = 1;
	ThreadSize.z = 1;
	//�����˺���
	CudaCaculateKernal <<<BlockSize, ThreadSize>>> (pCudaX, pCudaY, nLength);
	//�ȴ����������е��߳̽���
	cudaDeviceSynchronize();
	//�ͷ��ڴ�
	cudaFree(pCudaX);
	cudaFree(pCudaY);
}

//GPU����������ѯ   ����������1.0��ʼ
void QueryGPUCapcity(void)
{
	cudaDeviceProp prop;

	int count = 0;
	cudaGetDeviceCount(&count);
	printf("�Կ���֧�ֵ�cuda������������%d\n", count);
	for (int i = 0; i < count; ++i) 
	{
		cudaGetDeviceProperties(&prop, i);
		printf("----��%d���������Ļ�����Ϣ----\n", i + 1);
		printf("���������ƣ�%s \n", prop.name);
		printf("����������%d.%d\n", prop.major, prop.minor);
		printf("�豸��ȫ���ڴ�������%dMB\n", prop.totalGlobalMem / 1024 / 1024);
		printf("�豸�ϳ����ڴ�������%dKB\n", prop.totalConstMem / 1024);
		printf("һ���߳̿��п�ʹ�õ�������ڴ棺%dKB\n", prop.sharedMemPerBlock / 1024);
		printf("һ���߳����������߳�������%d\n", prop.warpSize);
		printf("һ���߳̿��пɰ���������߳�������%d\n", prop.maxThreadsPerBlock);
		printf("��ά�߳̿�������ÿһά�ɰ���������߳�������(%d,%d,%d)\n", prop.maxThreadsDim[0],
			prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
		printf("һ���̸߳���ÿһά�ɰ���������߳̿�������(%d,%d,%d)\n", prop.maxGridSize[0],
			prop.maxGridSize[1], prop.maxGridSize[2]);
	}
}
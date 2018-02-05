#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include"pathalg.h"
static const int WORK_SIZE =258;
void parallelor::copydata(int s,vector<edge>&edges,int nodenum){
	
};
void parallelor::dellocate(){
};
void parallelor::allocate(int maxn,int maxedge){
}
void parallelor::topsort()
{
	cout<<" in top sort "<<endl;
	queue<int>zero;
	vector<int>order(nodenum*LY,-1);
	for(int i=0;i<nodenum*LY;i++)
		zero.push(i);
	int biao=0;
	while(!zero.empty())
	{
		int node=zero.front();
		zero.pop();
		order[node]=biao++;
		for(int i=0;i<neibn[node].size();i++)
		{
			if((--ancestor[neibn[node][i]])==0)
				zero.push(neibn[node][i]);
		}
	}
	vector<pair<int,int>>tmp;
	for(int i=0;i<order.size();i++)
		tmp.push_back(make_pair(i,order[i]));
	sort(tmp.begin(),tmp.end(),pairless());
	for(int i=0;i<order.size();i++)
		ordernode.push_back(tmp[i].first);
};
void parallelor::init(pair<vector<edge>,vector<vector<int>>>ext,vector<pair<int,int>>stpair,vector<vector<int>>&relate,ginfo ginf)
{
	cout<<"in cuda init"<<endl;
	nodenum=ginf.pnodesize;
	edges=ext.first;
	vector<vector<int>>esigns;
	esigns=ext.second;
	mark=new int;
	*mark=0;
	W=WD+1;
	st=new int[2*edges.size()*LY];
	te=new int[2*edges.size()*LY];
	d=new int[nodenum*LY*YE];
	esignes=new int[edges.size()*LY];
	vector<vector<int>>nein(nodenum*LY,vector<int>());
	neibn=nein;
	vector<vector<int>>neie(nodenum,vector<int>());
	for(int i=0;i<edges.size();i++)
		{
			int s=edges[i].s;
			int t=edges[i].t;
			neibn[s].push_back(t);
			neibn[t].push_back(s);
			neie[s].push_back(i);
			neie[t].push_back(i);
		}
	int count=0;
	for(int k=0;k<LY;k++)
		for(int i=0;i<nodenum;i++)
			for(int j=0;j<neibn[i].size();j++)
			{
				st[count]=i;
				if(esigns[k][neie[i][j]]==-1)
					te[count]=i;
				te[count]=neibn[i][j];
				count++;
			}
	for(int i=0;i<nodenum*LY*YE;i++)
		d[i]=INT_MAX/2;
	/*for(int k=0;k<LY;k++)
	{
		int boff=k*YE*nodenum;
		for(int i=0;i<YE;i++)
		{
			int soff=i*nodenum;
			for(int j=0;j<stpair.size();j++)
				d[boff+soff+stpair[i].first]=0;
		}
	}*/
	for(int i=0;i<10;i++)
		cout<<d[i]<<endl;
	//cudaMalloc((void**)&dev_st,2*LY*edges.size()*sizeof(int));
	//cudaMalloc((void**)&dev_te,2*LYedges.size()*sizeof(int));
	//cudaMalloc((void**)&dev_d,YE*LY*nodenum*sizeof(int));
	//cudaMemcpy(dev_te,te,2*LY*edges.size()*sizeof(int),cudaMemcpyHostToDevice);
	//cudaMemcpy(dev_st,st,2*LY*edges.size()*sizeof(int),cudaMemcpyHostToDevice);
	//cudaMemcpy(dev_d,d,YE*LY*nodenum*sizeof(int),cudaMemcpyHostToDevice);
	cout<<"get out"<<endl;
	cout<<nodenum<<endl;
};
parallelor::parallelor()
{

};
__global__ void BFSfast(int *st,int *te,int *d,int round,int E,int N)
{
	int i = threadIdx.x + blockIdx.x*blockDim.x;
	int ye=i/(E*LY);
	int eid=(i%(E*LY));
	int ly=eid/E;
	int off=ye*N+ly*N*YE;
	int s=st[eid],t=te[eid];
	if(d[s+off]==round-1&&d[t+off]>round)
		d[t+off]=round;
}
vector<int> parallelor:: routalg(int s,int t,int bw)
{
	cout<<"blasting "<<endl;
	int kk=1;
	time_t start,end;
	start=clock();
	int size=edges.size()*LY*YE;
	for(int i=0;i<=WD;i++)
		BFSfast<<<size/512+1,512>>>(dev_st,dev_te,dev_d,i,edges.size(),nodenum);
	cudaMemcpy(d,dev_d,YE*LY*nodenum*sizeof(int),cudaMemcpyDeviceToHost);
	
	end=clock();
	cout<<"GPU time is : "<<end-start<<endl;
	cout<<"over!"<<endl;
	return vector<int>();
};
int fls(int x)
{
	int position;
	int i;
	if(x!=0)
		for(i=(x>>1),position=0;i!=0;++position)
			i>>=1;
	else
		position=-1;
	return pow(2,position+1);
}
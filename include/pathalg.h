//
// Created by root on 17-5-9.
//
#ifndef CSPALLOC_PATHALG_H
#include"limits.h"
#define CSPALLOC_PATHALG_H
#define INFCOST INT_MAX/2
#include<bits/stdc++.h>
#include <unistd.h>
#include"edge.h"
#include<sys/time.h>
#include<queue>
#define ML 50
#define BS 5
#define WD 5
#ifndef LY 
	#define LY 50
#endif
#define inf INT_MAX/2
using namespace std;
class pairless {
    public:
        bool operator()(pair<int,int>&a,pair<int,int>&b){
            return a.second<b.second;
        }
};
class algbase {
    protected:
        vector<int> getrout(int &s, int &t, vector<edge> &edges, vector<int> &pre) {
            vector<int> rout;
            int pp = pre[t];
            while (pp >= 0) {
                rout.push_back(pp);
                pp = pre[edges[pp].s];
            }
            reverse(rout.begin(), rout.end());
            return rout;
        }
    public:
        algbase(){};
        virtual bool cutcake(int)=0;
        virtual void init(pair<vector<edge>,vector<vector<int>>>extenedges,vector<pair<int,int>>stpair,vector<vector<int>>&relate,ginfo)=0;
	 	virtual vector<int> routalg(int s,int t,int bw)=0;
	 	virtual pair<int,int> prepush(int s,int t,int bw)=0;
};
class dijkstor:public algbase{
    public:
		vector<vector<int>>neibour;
		vector<int>ancestor;
		int edgesize,nodenum,pesize,pnodesize,maxbw;
		vector<vector<vector<int>>>mask;
		vector<edge>edges;
		vector<int>dist;
		vector<int>pre;
		vector<int>leveln;
		vector<int>exn2n;
		vector<vector<int>>rela;
		vector<int>order;
		vector<vector<vector<int>>>neie;
		vector<vector<vector<int>>>nein;
		vector<int>esign;
		vector<pair<int,int>>stes;
		int W;
        dijkstor(){};
        void topsort()
        {
        }
        virtual bool cutcake(int index){
        }
        virtual void init(pair<vector<edge>,vector<vector<int>>>extenedges,vector<pair<int,int>>stpair,vector<vector<int>>&relate,ginfo ginf){
        	cout<<"init in pa"<<endl;
        	maxbw=500;
        	rela=relate;
        	stes=stpair;
        	edges=extenedges.first;
        	vector<vector<int>>esigns=extenedges.second;
        	edgesize=edges.size(),nodenum=ginf.enodesize,pesize=ginf.pesize,pnodesize=ginf.pnodesize;
        	exn2n=ginf.exn2n;
        	vector<vector<int>>nd(nodenum*LY,vector<int>());
        	neibour=nd;
        	vector<int>ad(nodenum*LY,0);
        	ancestor=ad;	
    		vector<int>bl(BS,0);
    		leveln=bl;
    		vector<vector<vector<int>>>nm(BS,vector<vector<int>>());
    		mask=nm;
    		vector<int>dd(nodenum*LY,inf);
    		dist=dd;
    		vector<int>pp(nodenum*LY,-1);
    		pre=pp;
			pesize=edges.size();
			W=WD+1;
			//vector<vector<vector<int>>>tnein(LY,vector<vector<int>>());
			//vector<vector<vector<int>>>tneie(LY,vector<vector<int>>());
			//neie=tneie;
			//nein=tnein;
			cout<<"pnodesize is :"<<pnodesize<<endl;
			cout<<"neie size is "<<neie.size()<<endl;
			for(int k=0;k<LY;k++)
			{
				vector<vector<int>>tmpn(pnodesize,vector<int>());
				vector<vector<int>>tmpe(pnodesize,vector<int>());
				for(int i=0;i<edges.size();i++)
					{
						int s=edges[i].s;
						int t=edges[i].t;
						tmpn[s].push_back(t);
						tmpn[t].push_back(s);
						tmpe[s].push_back(esigns[k][i]);
						tmpe[t].push_back(esigns[k][i]);
					}
				
				neie.push_back(tmpe);
				nein.push_back(tmpn);
			}
			cout<<neie[1].size()<<" "<<nein[1].size()<<endl;
        }
        virtual vector<int> routalg(int s,int t,int bw){
        		cout<<"in rout alg"<<endl;
        		for(int k=0;k<LY;k++)
        		{
        			for(int l=0;l<stes.size();l++)
        			{
            			cout<<k<<" "<<l<<":"<<endl;
                		int tnode=-1;
        				vector<int>visited(pnodesize,0);
        				vector<int>pre(pnodesize,-1);
        				int vflag=1;
        				queue<int>que;
        				int s=stes[l].first;
        				int t=stes[l].second;
        				que.push(s);
        	        	visited[s]=1;
        				while(!que.empty()&&vflag)
        				{
        					int node=que.front();
        					que.pop();
        					for(int i=0;i<nein[k][node].size();i++)
        					{
        						
        						//cout<<nein[k][node][i]<<endl;
        						if(neie[k][node][i]>0)
        						{	
        							int to=nein[k][node][i];
        							if(visited[to]==0)
        							{
        								pre[to]=node;que.push(to);visited[to]=1;
        							}
        							else
        								continue;
        							if(to==t){tnode=to;vflag=0;break;}
        						}
        					}
        				}
        				int prn=tnode;
						int len=0;
						cout<<tnode<<" ";
						if(tnode>=0)
						{
							int prn=tnode;
							while(prn!=s)
							{
								cout<<prn<<" ";
								prn=pre[prn];
							}
							cout<<prn<<" ";
						}
						cout<<endl;
        			}
        				
        		}
        		return vector<int>();
	 	}
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        static bool compare(pair<int,int>&a,pair<int,int>&b)
        {
        	if(a.second<b.second)
        		return true;
        	return false;
        }
        virtual pair<int,int> prepush(int s,int t,int bw)
        {
        };
};
class parallelor:public algbase
{
	private:
		edge *dev_edges,*aedges;
		int*dev_m,*m,*dev_pre,*pre,*pred,*dev_pred,*dev_d,*d,*dev_mask,*mask,*dev_leveln,*leveln;
		int*dev_rela,*rela;
		int presize,dsize,masksize,levelnsize;
		int edgesize,nodenum,pesize,pnodesize;
		int neisize,duansize;
		int *choosel,*dev_choosel;
		int *rout,*dev_rout;
		int *routn,*dev_routn,*order,*dev_order;
		vector<int>hleveln,ancestor;
		int maxbw;
		int *dev_qian,*qian,*dev_qbeg,*qbeg,*dev_qsize,*qsize;
		epair *dev_nei,*nei;
		int *dev_duan,*duan;
		int *dev_beg,*beg;
		int *dev_value,*value;
		int *dev_height,*height;
		vector<vector<int>>neibour;
		vector<edge>edges;
		vector<int>ordernode;
		void allocate(int maxn,int maxedges);
		void copydata(int s,vector<edge>&edges,int nodenum);
		void dellocate();
		int W;
		int *st,*te,*dev_st,*dev_te;
		int *chan,*dev_chan;
		vector<vector<int>>neibn;
		int *mark,*dev_mark;
	public:
	 	 parallelor();
	 	 void topsort();
	 	 virtual pair<int,int> prepush(int s,int t,int bw){};
	 	 virtual bool cutcake(int index){};
	 	 virtual vector<int> routalg(int s,int t,int bw);
	 	 virtual ~parallelor(){dellocate();}
	 	 virtual void init(pair<vector<edge>,vector<vector<int>>>extenedges,vector<pair<int,int>>stpair,vector<vector<int>>&relate,ginfo ginf);
};
#endif //CSPALLOC_PATHALG_H

#include<bits/stdc++.h>
using namespace std;
class SegmentTree{
public:
vector<int> seg,lazy;
    SegmentTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }
    void build(int ind,int low,int high,vector<int>& arr){
        if(low==high){
            seg[ind]=arr[low];
            return;
        }
        int mid=(low+high)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    void update(int ind,int low,int high,int l,int r,vector<int>& arr){
        if(lazy[ind]!=0){
            seg[ind]=(high-low+1)-seg[ind];
            if(low!=high){
                lazy[2*ind+1]=!lazy[2*ind+1];
                lazy[2*ind+2]=!lazy[2*ind+2];
            }
            lazy[ind]=0;
        }
        //no overlap
        if(r<low || high<l) return;
        //complete overlap
        if(l<=low && high<=r){
            seg[ind]=(high-low+1)-seg[ind];
            if(low!=high){
                lazy[2*ind+1]=!lazy[2*ind+1];
                lazy[2*ind+2]=!lazy[2*ind+2];
            }
            return;
        }
        //partial overlap
        int mid=(low+high)/2;
        update(2*ind+1,low,mid,l,r,arr);
        update(2*ind+2,mid+1,high,l,r,arr);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    int query(int ind, int low, int high, int l, int r, vector<int> &arr){
        if(lazy[ind]!=0){
            seg[ind]=(high-low+1)-seg[ind];
            if(low!=high){
                lazy[2*ind+1]=!lazy[2*ind+1];
                lazy[2*ind+2]=!lazy[2*ind+2];
            }
            lazy[ind]=0;
        }
        //no overlap
        if(r<low || high<l) return 0;
        //complete overlap
        if(l<=low && high<=r){
            return seg[ind];
        }
        //partial overlap
        int mid=(low+high)/2;
        int left=query(2*ind+1,low,mid,l,r,arr);
        int right=query(2*ind+2,mid+1,high,l,r,arr);
        return left+right;
    }
};
int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){cin>>arr[i];}
    SegmentTree sgt(n);
    sgt.build(0,0,n-1,arr);
    // for(int &i:sgt.seg) cout<<i<<" ";
    int q;
    cout<<"Enter q:";
    cin>>q;
    while(q--){
        int type,l,r;
        cin>>type>>l>>r;
        if(type==0){
            sgt.update(0,0,n-1,l,r,arr);
            cout<<sgt.query(0,0,n-1,l,r,arr)<<"\n";
        }
        else {
            cout<<sgt.query(0,0,n-1,l,r,arr)<<"\n";
        }
    }    
}
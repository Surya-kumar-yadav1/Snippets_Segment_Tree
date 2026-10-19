//Range Update queries
#include<bits/stdc++.h>
using namespace std;
class SegmentTree{
public:
    vector<int> seg;
    vector<int> lazy;
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
    void update(int ind,int low,int high,int l,int r,int val,vector<int> &arr){
        //update the lazy nodes and lazy propagate to childs
        if(lazy[ind]!=0){
            seg[ind]+=(high-low+1)*val;
            if(low!=high){//agr lazy = +K hai toa sabse pehle seg ko update karo aur lazy propagate the same values to the childs
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            lazy[ind]=0;
        }
        //no overlap
        if(r<low || high<l) return;
        //complete overlap
        if(l<=low && high<=r){
            seg[ind]=(high-low+1)*val;
            lazy[2*ind+1]+=val;
            lazy[2*ind+2]+=val;
            return;
        }
        //partial overlap
        int mid=(low+high)/2;
        update(2*ind,low,mid,l,r,val,arr);
        update(2*ind+2,mid+1,high,l,r,val,arr);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    int query(int ind,int low,int high,int l,int r,int val){
        if(lazy[ind]!=0){
            seg[ind]+=(high-low+1)*val;
            if(low!=high){//agr lazy = +K hai toa sabse pehle seg ko update karo aur lazy propagate the same values to the childs
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
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
        int left=query(2*ind+1,low,mid,l,r,val);
        int right=query(2*ind+2,mid+1,high,l,r,val);
        return left+right;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    SegmentTree sgt(n);
    sgt.build(0,0,n-1,arr);
    int q;
    cin>>q;
    while(q--){
        int l,r,val;
        cin>>l>>r>>val;
        int res=sgt.query(0,0,n-1,l,r,val);
        cout<<res<<"\n";
    }
}
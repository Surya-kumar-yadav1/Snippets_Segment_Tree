#include<bits/stdc++.h>
using namespace std;
class SegmentTree{
public:
    vector<int> seg;
    SegmentTree(int n){
        seg.resize(4*n+1);
    }
    void build(int ind,int low,int high,vector<int>& arr){
        if(low==high){
            seg[ind]=arr[low];
            return;
        }
        int mid=(low+high)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
    }
    int query(int ind,int low,int high,int l,int r){
        //no overlap : [low high] [l r] or [l r] [low high]
        if(high<l || r<low) return INT_MAX;
        //complete Overlap : segRange[low high] and qRange[l r] -> [l low high r]
        if(low>=l && high<=r) return seg[ind];
        //partial Overlap : some part of segRange fall in qRange -> left ,right
        int mid=(low+high)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2,mid+1,high,l,r);
        return min(left,right);
    }
    //point update in segment Tree
    void update(int ind,int low,int high,int i,int val){
        if(low==high){
            seg[ind]=val;
            return;
        }
        int mid=(low+high)/2;
        if(i<=mid) update(2*ind+1,low,mid,i,val);
        else update(2*ind+2,mid+1,high,i,val);
        seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
    }
};
int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    SegmentTree seg1(n);
    seg1.build(0,0,n-1,arr);
    for(int &i:seg1.seg) cout<<i<<" ";
    cout<<"Query:"<<endl;
    int l,r;
    cin>>l>>r;
    cout<<seg1.query(0,0,n-1,l,r);
}
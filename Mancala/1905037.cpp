#include<bits/stdc++.h>
using namespace std;
int aa[14]= {4,4,4,4,4,4,0,4,4,4,4,4,4,0};
vector<int>ab(14,0);
stack<vector<int>>st;
int additional_move_earned_a=0,additional_move_earned_b=0;
int storage_a=6,storage_b=13,bin_cnt=14;
bool make_move(vector<int>& arr,int idx)
{
    int d=arr[idx];
    arr[idx]=0;
    for(int i=idx+1; i<=idx+d; i++)
    {
        arr[i%bin_cnt]++;
    }
    int last=(idx+d)%bin_cnt,player=(idx<6 ? 0 : 1);
    bool self_end=false;
    if(player==0&&last<6||player==1&&last>6)
        self_end=true;
    if(last!=storage_a&&last!=storage_b&&arr[last]==1&&arr[12-last]!=0&&self_end)
    {
        int n=arr[last]+arr[12-last];
        arr[last]=arr[12-last]=0;
        if(idx<6)
            arr[storage_a]+=n;
        else
            arr[storage_b]+=n;
    }
    return ((last==storage_a&&idx<6)||(last==storage_b&&idx>6));
}
bool is_gameover(vector<int>& arr)
{
    int sum=0,i;
    for(i=0; i<storage_a; i++)
    {
        sum+=arr[i];
    }
    if(sum==0)
        return true;
    for(i=storage_a+1; i<storage_b; i++)
    {
        sum+=arr[i];
    }
    if(sum==0)
        return true;
    return false;
}
int h1(vector<int>& arr)
{
    return arr[storage_a]-arr[storage_b];
}
int h2(vector<int>& arr)
{
    int sum=0,i,w1=10,w2=3;
    for(i=0; i<storage_a; i++)
    {
        sum+=arr[i];
    }
    for(i=storage_a+1; i<storage_b; i++)
    {
        sum-=arr[i];
    }
    return w1*h1(arr)+w2*sum;
}
int h3(vector<int>& arr,int player)
{
    int w3=1;
    if(player==0)
        return h2(arr)+w3*additional_move_earned_a;
    else
        return h2(arr)+w3*additional_move_earned_b;
}
int h4(vector<int>& arr,int player,int captured)
{
    int w4=5;
    return h3(arr,player)+w4*captured;
}

int calculated_move=-1;
int init_depth=10;
int calls=1;
int minimax(int depth,int alpha,int beta,int maximizingplayer,int captured)
{
    //cout<<"minimax("<<depth<<","<<alpha<<","<<beta<<","<<maximizingplayer<<")"<<endl;
    if(st.empty())
    {
        cout<<"error";
        exit(-1);
    }
    vector<int>arr=st.top();
    if(depth<=0||is_gameover(arr))
    {
        st.pop();
        return h4(arr,maximizingplayer,captured);
    }
    //cout<<"depth before calling "<<depth<<endl;
    int i,j;
    if(maximizingplayer==0)
    {
        int maxeval=-1e9;

        for(i=0; i<6; i++)
        {
            //if(depth==init_depth)
                //cout<<depth<<" "<<i<<endl;
            vector<int> brr(14);
            for(j=0; j<14; j++)
                brr[j]=arr[j];
            int eval;
            if(brr[i]==0)continue;
            bool f=make_move(brr,i);
            captured+=brr[6]-arr[6];
            st.push(brr);
            //cout<<"depth before calling "<<depth<<endl;
            if(f)
                eval=minimax(depth-1,alpha,beta,maximizingplayer,captured);
            else
                eval=minimax(depth-1,alpha,beta,!maximizingplayer,captured);
            if(depth==init_depth&&maxeval<eval)
                calculated_move=i;
            maxeval=max(maxeval,eval);
            alpha=max(alpha,eval);
            if(beta<=alpha)
            {
                //cout<<"breaking"<<endl;
                break;
            }
        }
        st.pop();
        return maxeval;
    }
    else
    {
        int mineval=1e9;

        for(i=0; i<6; i++)
        {
            //if(depth==init_depth)
                //cout<<depth<<" "<<i<<endl;
            vector<int> brr(14);
            for(j=0; j<14; j++)
                brr[j]=arr[j];
            int eval;
            if(brr[i+7]==0)continue;
            bool f=make_move(brr,i+7);
            st.push(brr);
            //cout<<"depth before calling "<<depth<<endl;
            if(f)
                eval=minimax(depth-1,alpha,beta,maximizingplayer,captured);
            else
                eval=minimax(depth-1,alpha,beta,!maximizingplayer,captured);
            if(depth==init_depth&&mineval>eval)
                calculated_move=i+7;
            mineval=min(mineval,eval);
            beta=min(beta,eval);
            if(beta<=alpha)
            {
                //cout<<"breaking"<<endl;
                break;
            }
        }
        st.pop();
        return mineval;
    }
}


int main()
{
    for(int i=0;i<14;i++)
        ab[i]=aa[i];
    int mv;
    while(true)
    {
        st.push(ab);
        minimax(init_depth,-1e9,1e9,0,0);
        cout<<calculated_move<<endl;
        while(make_move(ab,calculated_move))
        {
            additional_move_earned_a++;
            st.push(ab);
            minimax(init_depth,-1e9,1e9,0,0);
            cout<<calculated_move<<endl;
        }
        cin>>mv;
        if(mv==-1)
        {
            for(int i=0;i<14;i++)
                cout<<ab[i]<<" ";
            cout<<endl;
            cin>>mv;
        }
        while(make_move(ab,mv))
        {
            additional_move_earned_b++;
            cin>>mv;
        }
    }

}
/*
1
9
11
1
10
0
1
12
2
12
11
12
10
3
12
7
12
11
12
10
5*/


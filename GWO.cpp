#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<b;i++)
#define rrep(i,b,a) for(int i=b;i>=a;i--)
#define um unordered_map
#define us unordered_set
#define vi vector<int> 
#define vi2d vector<vector<int>>
#define fori(a) for(auto i : a )
#define all(a) begin(a), end(a)
#define set(a,b) memset(a,b,sizeof(a))
#define pi 3.14159
#define int long long int
#define ll long long
#define ull unsigned long long
#define pb push_back
#define PF push_front //deque
#define mp make_pair
#define pq priority_queue
const int mod=1e9+7;
const int N = 1e6 + 7;
#define f first
#define s second
#define pii pair< int, int >
#define so(v) sort(v.begin(), v.end())
#define tc int t; cin >> t; while(t--)
#define deb1a(v)                  \
    cout << #v << "--->" << endl; \
    for (auto it : v)             \
        cout << it << " ";        \
    cout << endl;
#define deb2a(v)                  \
    cout << #v << "--->" << endl; \
    for (auto it : v)             \
    {                             \
        for (auto it1 : it)       \
        {                         \
            cout << it1 << " ";   \
        }                         \
        cout << endl;             \
    }
#define deb3a(v)                               \
    cout << #v << "-->" << endl;               \
    for (auto it : v)                          \
    {                                          \
        cout << it.fi << " " << it.se << endl; \
    }

void optimizeIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

/*void IO(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}*/

///////////////////////////////////////////////////////////////////////////////////////////

double fitness(vector<double> position)
{
    double fitness_value = 0.0;
    for(int i=0;i<position.size();i++)
    {
        double xi = position[i];
        fitness_value += (xi*xi);
    }
    return fitness_value;
}

class wolf
{
public:
    vector<double> position;
    double fitness;
    double rnd;
    wolf(double maxx, double minx, int dim)
    {
        this->rnd = ((double) rand() / (RAND_MAX));
        this->position.resize(dim, 0.0);

        for(int i=0;i<dim;i++)
        {
            this->position[i] = ((maxx - minx) * this->rnd + minx);
        }
        this->fitness = fitness(this->position);
    }
};

static bool cmp(wolf &a, wolf &b)
{
    return a.fitness < b.fitness;
}


vector<double> gwo(float fitness, int max_iter, int n, int dim, int minx, int maxx)
{
    double rnd = ((double) rand() / (RAND_MAX));

    vector<wolf> population;

    sort(population.begin(), population.end(), cmp);

    wolf alpha_wolf = population[0];
    wolf beta_wolf = population[1];
    wolf delta_wolf = population[2];

    int iter = 0;

    while(iter < max_iter)
    {
        if(iter%10 == 0 && iter > 1)
        {
            cout<<"Iter = "<<iter<<" best fitness = %.3f"<<alpha_wolf.fitness<<"\n";
        }

        double a = 2 * (1 - iter/max_iter);

        for(int i=0;i<n;i++)
        {
            double A1 = a * (2 * rnd - 1);
            double A2 = a * (2 * rnd - 1);
            double A3 = a * (2 * rnd - 1);

            double C1 = 2 * rnd;
            double C2 = 2 * rnd;
            double C3 = 2 * rnd;

            vector<double> X1(dim, 0);
            vector<double> X2(dim, 0);
            vector<double> X3(dim, 0);
            vector<double> Xnew(dim, 0);

            for(int j=0;j<dim;j++)
            {
                double D_alpha = abs(C1 - alpha_wolf.position[j] - population[i].position[j]);
                double D_beta = abs(C1 - beta_wolf.position[j] - population[i].position[j]);
                double D_delta = abs(C1 - delta_wolf.position[j] - population[i].position[j]);

                X1[j] = alpha_wolf.position[j] - A1 * D_alpha;
                X2[j] = beta_wolf.position[j] - A2 * D_beta;
                X3[j] = delta_wolf.position[j] - A3 * D_delta;

                Xnew[j]+= X1[j] + X2[j] + X3[j];
            }

            for(int j=0;j<dim;j++)
            {
                Xnew[j] /= 3.0;
            }

            double fnew = fitness(Xnew);

            if(fnew < population[i].fitness)
            {
                population[i].position = Xnew;
                population[i].fitness = fnew;
            }

        }
        sort(population.begin(), population.end(), cmp);

        wolf alpha_wolf = population[0];
        wolf beta_wolf = population[1];
        wolf delta_wolf = population[2];

        iter++;
    }
    return alpha_wolf.position;
}

int32_t main()
{
    optimizeIO();
    int dim = 3;

    int num_particles = 50;
    int max_iter = 200;

    vector<double> position(num_particles, 0.0);

    for(int i=0;i<num_particles;i++)
    {
        position[i] = i*(1.0);
    }

    double fit = fitness(position);

    vector<double> best_position = gwo(fit, max_iter, num_particles, dim, -10.0, 10.0);

    cout<<"Best Solution found is : \n";

    for(auto it:best_position)
    {
        cout<<it<<" ";
    }

    return 0;
}

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<complex<double>> &a, bool inv){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int b=n>>1;
        for(; j&b; b>>=1) j-=b;
        j+=b;
        if(i<j) swap(a[i],a[j]);
    }
    for(int l=2;l<=n;l<<=1){
        double ang=2*M_PI/l*(inv?-1:1);
        complex<double> wlen(cos(ang),sin(ang));
        for(int i=0;i<n;i+=l){
            complex<double> w(1);
            for(int j=0;j<l/2;j++){
                complex<double> u=a[i+j], v=a[i+j+l/2]*w;
                a[i+j]=u+v;
                a[i+j+l/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(inv) for(auto &x:a) x/=n;
}
 
vector<double> conv(const vector<double> &a, const vector<double> &b){
    int n=1;
    while(n < a.size()+b.size()-1) n<<=1;
    vector<complex<double>> fa(n), fb(n);
    for(int i=0;i<a.size();i++) fa[i]=a[i];
    for(int i=a.size();i<n;i++) fa[i]=0;
    for(int i=0;i<b.size();i++) fb[i]=b[i];
    for(int i=b.size();i<n;i++) fb[i]=0;
    fft(fa,false);
    fft(fb,false);
    for(int i=0;i<n;i++) fa[i]*=fb[i];
    fft(fa,true);
    vector<double> r(n);
    for(int i=0;i<n;i++) r[i]=round(fa[i].real());
    return r;
}
typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=ll(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	FOR(i,0,sz(a)) L[i] = C((ll)a[i] / cut, (ll)a[i] % cut);
	FOR(i,0,sz(b)) R[i] = C((ll)b[i] / cut, (ll)b[i] % cut);
	fft(L, false), fft(R, false);
	FOR(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl, false), fft(outs, false);
	FOR(i,0,sz(res)) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

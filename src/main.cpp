#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include<bitset>
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>

using namespace libsnark;
using namespace std;

vector<vector<string>> read_csv(string path) {
    ifstream _csvInput(path);
    vector<vector<string>> data;
    string data_line;
    int i = 0;
    getline(_csvInput, data_line);
    while (getline(_csvInput, data_line)) {
        vector<string> line;
        string str;
        stringstream sline(data_line);
        int k = 1;
        while (getline(sline, str, ';')) {
            if (!(k == 1 || (k >= 11 && k <= 14) || (k >= 16 && k <= 20))) {
                str.erase(0, 1);
                str.erase(str.size() - 1, 1);
            }
            line.push_back(str);
            k++;
        }
        data.push_back(line);
        i++;
    }
    return data;
}
vector<string> get_col(vector<vector<string>> data, int col_num) {
    vector<string> col_data;
    vector<string> temp_vect;
    for (vector<vector<string>>::iterator ite = data.begin(); ite != data.end(); ite++) {
        temp_vect = *ite;
        col_data.push_back(temp_vect[col_num]);
    }
    return col_data;
}
int main()
{
    /////////////////////////////common_var//////////////////////////////////
    int time[4];//time
    vector<int> age_result,sel_result;//check_age_result
    ////////////////////////////////////read data/////////////////////////
    auto start = std::chrono::steady_clock::now();
    vector<vector<string>> data = read_csv("/home/niecf/code/src/bank-additional.csv");
    vector<string> col_data ;
    auto finish = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    //std::cout << "time:"<<duration.count() << "ms" << std::endl;
    //time[0][1]=duration.count();
    /*
    for (vector<string>::iterator ite = col_data.begin(); ite != col_data.end(); ite++) {
        cout <<distance(col_data.begin(),ite)<<" "<< *ite <<endl;
    }
    */
   
   ///////////////////////check_age///////data_range/////////////////
   
   {
    auto start1 = std::chrono::steady_clock::now();
    col_data = get_col(data, 0);
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    pb_variable<FieldT> x, max,min;
    pb_variable<FieldT> less, less_or_eq;

    x.allocate(pb, "x");
    max.allocate(pb, "max");
    min.allocate(pb,"min");
    less.allocate(pb, "less"); // must have
    less_or_eq.allocate(pb, "less_or_eq");
    
    pb.val(max)= 60;
    pb.val(min)=18;

    comparison_gadget<FieldT> cmp(pb, 10, x, max, less, less_or_eq, "cmp");
    cmp.generate_r1cs_constraints();
    comparison_gadget<FieldT> cmp1(pb, 10, min, x, less, less_or_eq, "cmp");
    cmp1.generate_r1cs_constraints();
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(less_or_eq, 1, FieldT::one()));

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();

    for (vector<string>::iterator ite = col_data.begin(); ite != col_data.end(); ite++) {
        string s_data=*ite;
        int data_tmp= atoi(s_data.c_str());

        // Add witness values
        start = std::chrono::steady_clock::now();
        pb.val(x) = data_tmp; // secret
        cmp.generate_r1cs_witness();
        cmp1.generate_r1cs_witness();

        // generate proof
        const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
        finish = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        time[1]+=duration.count();
        // verify
        start = std::chrono::steady_clock::now();
        bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
        
        finish = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        age_result.push_back(verified);
        time[2]+=duration.count();
    }
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();
    cout<<"setup times:"<<time[0]<<"ms"<<endl;
    cout<<"proof times:"<<time[1]<<"ms"<<endl;
    cout<<"verify times:"<<time[2]<<"ms"<<endl;
    cout<<"total times:"<<time[3]<<"ms"<<endl;

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
   }
   
   ////////////////////check_select_data//////////////////////////
   /*
   {
    auto start1 = std::chrono::steady_clock::now();
    col_data = get_col(data, 9);
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> a[3];
    pb_variable<FieldT> b[5][3];
    pb_variable<FieldT> t[5][4];
    pb_variable<FieldT> r[5];
    pb_variable<FieldT> r_t[3];
    pb_variable<FieldT> out;
   

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes    
    out.allocate(pb, "out");
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            b[i][j].allocate(pb,"b"+to_string(i)+to_string(j));
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
            t[i][j].allocate(pb,"t"+to_string(i)+to_string(j));
        }
        r[i].allocate(pb,"r"+to_string(i));
    }
    for(int i=0;i<3;i++){
        a[i].allocate(pb,"a"+to_string(i));
        r_t[i].allocate(pb,"r_t"+to_string(i));
    }
    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(16);

    // Add R1CS constraints to protoboard
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            pb.add_r1cs_constraint(r1cs_constraint<FieldT>(b[i][j]-a[j], 1, t[i][j]));
        }
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(t[i][0]+t[i][1], 1, t[i][3]));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(t[i][3]+t[i][2], 1, r[i]));
    }
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(r[0], r[1], r_t[0]));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(r_t[0], r[2],r_t[1]));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(r_t[1], r[3], r_t[2]));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(r_t[2], r[4], out));

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();
    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);

    // Add public input and witness values
    //int aa=1,bb=0;
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();

    const char* tar_value[]={"fri","mon","wed","thu","tue"};
    pb.val(out) = 0;
    for(int i=0;i<5;i++){
            for(int j=0;j<3;j++){
                pb.val(b[i][j])=int(tar_value[i][j]);
            }
        }
    for (vector<string>::iterator ite = col_data.begin(); ite != col_data.end(); ite++){
        string s_data=*ite;//get current value
        const char* str1=s_data.c_str();
        start = std::chrono::steady_clock::now();
        for(int i=0;i<3;i++){
            pb.val(a[i])=int(str1[i]);
        }
        
        for(int i=0;i<5;i++){
            for(int j=0;j<3;j++){
                pb.val(t[i][j])=pb.val(b[i][j])-pb.val(a[j]);
            }
            pb.val(t[i][3])=pb.val(t[i][0])+pb.val(t[i][1]);
            pb.val(r[i])=pb.val(t[i][3])+pb.val(t[i][2]);
        }
        pb.val(r_t[0])=pb.val(r[0])*pb.val(r[1]);
        pb.val(r_t[1])=pb.val(r_t[0])*pb.val(r[2]);
        pb.val(r_t[2])=pb.val(r_t[1])*pb.val(r[3]);
        
        const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
        finish = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        time[1]+=duration.count();
        // verify
        start = std::chrono::steady_clock::now();
        bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
        finish = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        time[2]+=duration.count();
        sel_result.push_back(verified);

    }
     for (vector<int>::iterator ite = sel_result.begin(); ite != sel_result.end(); ite++) {
        if(*ite==0)
            cout <<distance(sel_result.begin(),ite)<<" "<< *ite <<" "<<col_data[distance(sel_result.begin(),ite)]<<endl;
    }
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();
    cout<<"setup times:"<<time[0]<<"ms"<<endl;
    cout<<"proof times:"<<time[1]<<"ms"<<endl;
    cout<<"verify times:"<<time[2]<<"ms"<<endl;
    cout<<"total times:"<<time[3]<<"ms"<<endl;

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
   }
   */
    return 0;
}


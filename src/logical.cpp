#include <iostream>
#include <string>
#include <chrono>
#include <bitset>
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>

using namespace libsnark;
using namespace std;

int main () {
    int time[4];//time
    auto start = std::chrono::steady_clock::now();
    auto finish = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    /*
    {
    cout<<"**********************xor**************************"<<endl;
    auto start1 = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> out;
    pb_variable<FieldT> b;
    pb_variable<FieldT> a;
    pb_variable<FieldT> t1;
    pb_variable<FieldT> t2;
    pb_variable<FieldT> t3;

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes    
    out.allocate(pb, "out");
    b.allocate(pb, "b");
    a.allocate(pb, "a");
    t1.allocate(pb, "t1");
    t2.allocate(pb, "t2");
    t3.allocate(pb, "t3");

    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(1);

    // Add R1CS constraints to protoboard
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a, b, t1));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(2, t1, t2));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(b-t2, 1, t3));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a+t3, 1, out));
    
    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();
    // Add public input and witness values
    start = std::chrono::steady_clock::now();
    pb.val(out) = 0;
    pb.val(b) = 0;

    pb.val(a) = 0;
    pb.val(t1) = 0;
    pb.val(t2) = 0;
    pb.val(t3) = 0;

    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[1]=duration.count();
    // verify
    start = std::chrono::steady_clock::now();
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[2]=duration.count();
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;
    }
    */
   /*
    {
    cout<<"**********************and**************************"<<endl;
    auto start1 = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> out;
    pb_variable<FieldT> b;
    pb_variable<FieldT> a;

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes    
    out.allocate(pb, "out");
    b.allocate(pb, "b");
    a.allocate(pb, "a");


    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(1);

    // Add R1CS constraints to protoboard

    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a, b, out));

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();

    // Add public input and witness values
    start = std::chrono::steady_clock::now();
    pb.val(out) = 1;
    pb.val(b) = 1;

    pb.val(a) = 1;

    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[1]=duration.count();
    // verify
    start = std::chrono::steady_clock::now();
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[2]=duration.count();
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;
    }
    */
/*
    {
    cout<<"**********************or**************************"<<endl;
    auto start1 = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> out;
    pb_variable<FieldT> b;
    pb_variable<FieldT> a;
    pb_variable<FieldT> t1;
    pb_variable<FieldT> t2;

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes    
    out.allocate(pb, "out");
    b.allocate(pb, "b");
    a.allocate(pb, "a");
    t1.allocate(pb,"t1");
    t2.allocate(pb,"t2");

    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(1);

    // Add R1CS constraints to protoboard

    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a, b, t1));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(b-t1, 1, t2));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a+t2, 1,out));

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();
    // Add public input and witness values
    start = std::chrono::steady_clock::now();
    pb.val(out) = 1;
    pb.val(b) = 1;

    pb.val(a) = 0;
    pb.val(t1)=0;
    pb.val(t2)=1;

    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[1]=duration.count();
    // verify
    start = std::chrono::steady_clock::now();
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[2]=duration.count();
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;
    }
    */
/*
    {
    cout<<"**********************byte_xor**************************"<<endl;
    auto start1 = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> c[8];
    pb_variable<FieldT> b[8];
    pb_variable<FieldT> a[8];
    pb_variable<FieldT> t1[8];
    pb_variable<FieldT> t2[8];
    pb_variable<FieldT> t3[8];

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes   
    for(int i=0;i<8;i++){
        c[i].allocate(pb,"c"+to_string(i));
    }
    for(int i=0;i<8;i++){
        a[i].allocate(pb,"a"+to_string(i));
        b[i].allocate(pb,"b"+to_string(i));
        t1[i].allocate(pb, "t1_"+to_string(i));
        t2[i].allocate(pb, "t2_"+to_string(i));
        t3[i].allocate(pb, "t3_"+to_string(i));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a[i], b[i], t1[i]));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(2, t1[i], t2[i]));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(b[i]-t2[i], 1, t3[i]));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a[i]+t3[i], 1, c[i]));
    } 

    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(8);

    // Add R1CS constraints to protoboard
    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();
    // Add public input and witness values
    start = std::chrono::steady_clock::now();
    string str_a="11001101",str_b="10010011",str_c="01011110";
    bitset<8> bit_a(str_a),bit_b(str_b),bit_c(str_c);
    for(int i=0;i<8;i++){
        pb.val(c[i])=int(bit_c[i]);
        pb.val(b[i]) =int(bit_b[i]);
        pb.val(a[i]) =int(bit_a[i]);
        pb.val(t1[i]) =pb.val(a[i])*pb.val(b[i]);
        pb.val(t2[i])=pb.val(t1[i])*2;
        pb.val(t3[i])=pb.val(b[i])-pb.val(t2[i]);
    }


    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[1]=duration.count();
    // verify
    start = std::chrono::steady_clock::now();
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[2]=duration.count();
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;
    }
    */
   /*
   {
    cout<<"**********************byte_and**************************"<<endl;
    auto start1 = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> c[8];
    pb_variable<FieldT> b[8];
    pb_variable<FieldT> a[8];


    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes    
    for(int i=0;i<8;i++){
        c[i].allocate(pb,"c"+to_string(i));
        
    }
    for(int i=0;i<8;i++){
        a[i].allocate(pb,"a"+to_string(i));
        b[i].allocate(pb,"b"+to_string(i));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a[i], b[i], c[i]));
    }

    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(8);

    // Add R1CS constraints to protoboard

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();
    // Add public input and witness values
    start = std::chrono::steady_clock::now();
    string str_a="11001101",str_b="10010011",str_c="10000001";
    bitset<8> bit_a(str_a),bit_b(str_b),bit_c(str_c);
    for(int i=0;i<8;i++){
        pb.val(c[i])=int(bit_c[i]);
        pb.val(b[i]) =int(bit_b[i]);
        pb.val(a[i]) =int(bit_a[i]);
    }

    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[1]=duration.count();
    // verify
    start = std::chrono::steady_clock::now();
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[2]=duration.count();
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();
    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;
   }
  */ 
  
  {
    cout<<"**********************byte_or**************************"<<endl;
    auto start1 = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    libff::inhibit_profiling_counters = true;
    libff::inhibit_profiling_info = true;
  
    // Create protoboard
    protoboard<FieldT> pb;

    // Define variables
    pb_variable<FieldT> c[8];
    pb_variable<FieldT> b[8];
    pb_variable<FieldT> a[8];
    pb_variable<FieldT> t1[8];
    pb_variable<FieldT> t2[8];

    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes   
    for(int i=0;i<8;i++){
        c[i].allocate(pb,"c"+to_string(i));
        
    } 
    for(int i=0;i<8;i++){
        a[i].allocate(pb,"a"+to_string(i));
        b[i].allocate(pb,"b"+to_string(i));
        t1[i].allocate(pb, "t1_"+to_string(i));
        t2[i].allocate(pb, "t2_"+to_string(i));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a[i], b[i], t1[i]));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(b[i]-t1[i],1,t2[i]));
        pb.add_r1cs_constraint(r1cs_constraint<FieldT>(a[i]+t2[i],1,c[i]));
    }


    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(8);

    // Add R1CS constraints to protoboard
    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[0]=duration.count();
    // Add public input and witness values
    start = std::chrono::steady_clock::now();
    string str_a="11001101",str_b="10010011",str_c="11011111";
    bitset<8> bit_a(str_a),bit_b(str_b),bit_c(str_c);
    for(int i=0;i<8;i++){
        pb.val(c[i])=int(bit_c[i]);
        pb.val(b[i]) =int(bit_b[i]);
        pb.val(a[i]) =int(bit_a[i]);
        pb.val(t1[i]) =pb.val(a[i])*pb.val(b[i]);
        pb.val(t2[i])=pb.val(b[i])-pb.val(t1[i]);

    }

    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[1]=duration.count();
    // verify
    start = std::chrono::steady_clock::now();
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);
    finish = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    time[2]=duration.count();
    auto finish1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    time[3]=duration1.count();

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;
  }
  
 cout<<"setup times:"<<time[0]<<"ms"<<endl;
    cout<<"proof times:"<<time[1]<<"ms"<<endl;
    cout<<"verify times:"<<time[2]<<"ms"<<endl;
    cout<<"total times:"<<time[3]<<"ms"<<endl;
    return 0;
}
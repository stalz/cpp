//main.hpp
#ifndef _AP_MAIN_HPP
#define _AP_MAIN_HPP


//base types
//God help me for adding the lame type replacements,
//but I truly did have some experiments in mind.
#include <string>
namespace ap
{
    //The c++ spec fails to define the exact depth or sign of char,
    //so don't make assumptions about either.
    typedef char Chr;

    //TODO try flexstring or other drop-in replacements
    //the std::string is more of a "don't care what char realy is" container,so...
    //TODO need a UTF-8 capable string eventually
    typedef std::string Str;

    //The depth of these types is up to the platform/enviornment,
    //but will always be the min depth required for array[i] access:
    //Typically 32 or 64 bits, but don't assume size_t(-1) == SIZE_MAX.
    //(ptrdiff_t is the type that results from pointer subtraction)
    //Use {for(Np i(0); i<n: ++i) a[i]=0;} instead of {for(int i...}
    //Use {memset(ptr, sizeof(T), 0);}
    //TODO need a good constant defined for the max of these two...
    typedef size_t      Nsz;
    typedef ptrdiff_t   Npd;

    //TODO need a max defined for all of these char types
    typedef signed char     Ns1;

    //Used as the 'raw byte'
    //Always use unsigned chars for ascii
    typedef unsigned char   Nu1;

    //16 and 32 bit numbers
    #ifdef WIN32
    typedef __int16_t   Ns2;
    typedef __uint16_t  Nu2;
    typedef __int32_t   Ns4;
    typedef __uint32_t  Nu4;
    #else
    typedef int16_t     Ns2;
    typedef uint16_t    Nu2;
    typedef int32_t     Ns4;
    typedef uint32_t    Nu4;
    #endif
    typedef long long           Ns8;
    typedef unsigned long long  Nu8;

    //TODO bool?  why is bool more than one char, which is the smallest addressable bit length allowed by the lang c++ itself...?


    //TODO templates to auto construct further 2^n POD types?
    //template <Ns8 = > struct Nu {  };

    //TODO - float types?

    //TODO - helper functions?
    //  float compares?
    //  f

    //Tests
    //TODO
    //Need test to verify that:
    //  all have the required bit depth
    //  note the depth of size_t, and all others not used here (int, long, long int, etc.)
    //  note the SIZE_MAX and PTRDIFF_MAX, and if different can typically assumed bit depth
    //  should all number (N) types above have predictable rollover?
    //  std::limits agrees with sizeof(everything above)
    //  run typical use cases, or identity cases for the purpose of tutorial / example as much as test.
    //  note size and traits of char
}


//container types from stl
//For now, using std::vector as the sequence container of choice,
//and std::set as the associative container of choice...
//
//I expect the number of these types used will shrink dramatically
//as projects/apps get completed and profiling trims it down.
//So then this complete file will move to an example or starter-kit
//lib, and the minimally complete set for each app stay with it.
//
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <string>
namespace ap
{
    //TODO remove most of these, only declare a subset that is expected to be commonly used?

    //typedef std::vector<Chr> ChrVec; //um...don't let them...
    typedef std::vector<Str> StrVec;
    typedef std::vector<Nsz> NszVec;

    /*
    typedef std::vector<Ns1> Ns1Vec;
    typedef std::vector<Nu1> Nu1Vec;
    typedef std::vector<Ns2> Ns2Vec;
    typedef std::vector<Nu2> Nu2Vec;
    typedef std::vector<Ns4> Ns4Vec;
    typedef std::vector<Nu4> Nu4Vec;
    typedef std::vector<Ns8> Ns8Vec;
    typedef std::vector<Nu8> Nu8Vec;
    */

    //std::set is the default "sorted tree" type of choice
    typedef std::set<Chr> ChrSet;
    typedef std::set<Str> StrSet;
    typedef std::set<Nsz> NszSet;

    /*
    typedef std::set<Npd> NpdSet;
    typedef std::set<Ns1> Ns1Set;
    typedef std::set<Nu1> Nu1Set;
    typedef std::set<Ns2> Ns2Set;
    typedef std::set<Nu2> Nu2Set;
    typedef std::set<Ns4> Ns4Set;
    typedef std::set<Nu4> Nu4Set;
    typedef std::set<Ns8> Ns8Set;
    typedef std::set<Nu8> Nu8Set;
    */

    //TODO pair or tuple?

    //TODO bitfield solution examples


    //Tests
    //TODO
    //  verify containers (strings too) really handle holding exactly SIZE_MAX before failing?
    //  verify containers can perform typical operations on all data typse defined above and compile, etc
    //  run typical use cases, or identity cases for the purpose of tutorial / example as much as test.
    //  std container helper function idioms, maybe not as functions but at least comments with tutorial or sample usage...
    //  warn if SIZE_MAX != Str.GetMaxCapacity(), or similar other

    //remember, searching with comparrison-based sorted-trees such as std::set.find() often
    //does NOT out perform std::vector.find() O(n) when container sizes are less than 10,000 or 1,000...


    //bit field examples, limited of course, explained in comments, using sub byte precision to eliminate space makes most execute slower, and some take up MORE memory!


    // General Tips
    //  you can use C arrays[] in std containers, because pointers can be used as iterators
    //  don't try "container independant code"
    //  never use vector<bool>
    //  never use stl containers of auto_ptrs, never multi-maps of shared_ptr!
    //  stl <everthing> is copy happy: (1) copy+construction must be efff, (2) never store base-classes or auto_ptrs
    //  ALL stl sequence conts support range:
    //      construction:       T::T(src_begin, src_end)
    //      insertion:          t.insert(dest, src_begin, src_end)
    //      assign:             t.assign(src_begin, src_end)
    //
    //  ALL stl conts support range:
    //      erase:              t.erase(begin, end)
    //
    //

    template <typename T> bool  FooPredicate(const T & t) { return (t == T()); }
    template <typename T> T     Foo(const T & t) { return t+t; }

    void Test()
    {
        using namespace std;

        //typically used example vars
        const size_t    X(0);
        const size_t    LEN(1);
        const char      C('z');
        set<size_t>     s;
        vector<size_t>  v,v1,v2,v3;
        string          str;
        deque<size_t>   d;



        //Given v1 and v2, how best to set v1's entire contents to match the second half of v2's?
        {
            //Never forget the assign() function!  Best way when you have both iters to source data,
            //The best choice when you need to replace all contents, but operator=() won't work...
            v1.assign(v1.begin(), v2.begin() + (v2.size() / 2), v2.end());

            //TODO split between the above example and other stuff
            //..hhhmmmm...  Not in this case...
            size_t a[LEN];
            //...work on a...
            v1.insert(v1.begin(), a, a + LEN); //you can use pointers as random-access iterators like this

            //or
            const vector<size_t> V4(a, a + LEN);

            //or
            vector<size_t> v5;
            v5.reserve(MAX);
            memcpy(& v5[0], data, MAX);
            //
        }


        //typical use cases
        {
            //removing
            //for sequential contiguous stl container (vector, string, deque)
            //always use the erase remove idioms, so that it works first by swaping (remove on seq cont), then erasing from the end by resizing...

            //remove all equal to ...
            vec.erase( remove(vec.begin(), vec.end(), 123), vec.end());
            str.erase( remove(str.begin(), str.end(), 'z'), str.end());

            //remove all satisfying predicate ... (or where Foo(nextContained) == true)
            vec.erase( remove_if(vec.begin(), vec.end(), FooPredicate), vec.end());
            str.erase( remove_if(str.begin(), str.end(), FooPredicate), str.end());

            //don't just erase/remove, but also do something else, which means no more one liners like above
            //Remember that stl seq conts erase() returns what you need to update your loop's itr with
            {
                //start out by just operating on each contained
                //ignore std::transform() for now, for demonstration

                //old school for loop
                //this works fine, but not recc for gen use due to less safe [i]
                const size_t SIZE(/*...*/);
                for(size_t i(0); i<SIZE; ++i)  vec[i] = Foo(vec[i]);
                for(size_t i(0); i<SIZE; ++i)  str[i] = Foo(str[i]);

                //op on each, classic stl iter style
                //this works fine, but maybe prefer std::for_each or BOOST_FOREACH?
                {
                    typedef vector<size_t>::iterator Iter_t;
                    const Iter_t END(vec.end());
                    for(Iter_t i(vec.begin()); END != i; ++i)  (*i) = Foo(*i);
                }

                //ok now operate on all equal to ..., THEN remove
                {
                    const vector<size_t>::const_iterator END(vec.end());
                    for(vector<size_t>::iterator i(vec.begin()); END != i; /*not here!*/)
                    {
                        if (X == (*i))
                        {
                            Foo(*i);
                            i = vec.erase(i);
                        }
                        else
                            ++i;
                    }
                }
                //or
                {
                    const vector<size_t>::iterator       i(vec.begin());
                    const vector<size_t>::const_iterator END(vec.end());
                    while(END != i)
                    {
                        if (X == (*i))
                        {
                            Foo(*i);
                            i = vec.erase(i);
                        }
                        else
                            ++i;
                    }
                }



            }

            //for associative containers
            {

            }
        }
    }

    /*

    ifstream myFile("intlist.dat");
    list<int> myIntList( istream_iterator<int>(myfile), istream_iterator<int>()); //just a function def!

    //THIS ONE ALWAYS WORKS
    const istream_iterator<int> B( myFile );
    const istream_iterator<int> E();
    list<int> myIntList(B, E);

    //WE WISH THIS ALWAYS WORKED
    list<int> myIntList( (istream_iterator<int>(myfile)), istream_iterator<int>()); //fills myIntList





    */


    //StringHelp
    //  use of CStrings?
    //  can ALL functions work if all ops invalidate all iters?
}


//tinker macros
//  will return ref, will passbyref,
//
//  log/report
//  try/catch
//  throw?
//  assert or throw



//utilities?
namespace ap
{
    //shared_ptr (boost, tr1, etc
    //auto_ptr?
    //rand
    //
}


namespace template_testing
{
    struct StructEmpty_t {};
    struct StructInt_t { int i_; } StructInt;

    //
    // const return types
    //  Without return type const, any non-class type (int/size_t/double/etc)
    //  could fail this way if(GetSize() = X).  The return type of GetSize()
    //  is an rvalue, which cannot be assigned to unless it is a class-type.
    //
    //  So...

    //good, should NOT warn, and didn't.
    size_t  GetNonConstSize() { return 0; }
    bool    GetNonConstBool() { return true; }

    //excessive, should warn, and did in gcc4.4.5 on 11-28-2010
    //const size_t GetConstSize() const { return 0; }

    //should warn if wise, but that would require mind reading, T0D0
    StructInt_t GetNonConstt() { return StructInt; }

    //good, should not warn
    const StructInt_t GetConst() { return StructInt; }



    template <typename T> bool IsLastGreaterThanFirst(const T & CONT)
    {
        typename T::const_iterator B( CONT.begin() );
        typename T::const_iterator E( CONT.end() );
        return ((* (--E)) > (* B));
    }

    template <typename T> struct StructMemberConstructor
    {
        StructMemberConstructor(const T & X = T()) : t_(X) {}
        T t_;
    };

    void Test()
    {
        using namespace ap;

        StrVec sv;
        IsLastGreaterThanFirst(sv);

        StructMemberConstructor<Nsz> smc(0);
    }
}

#endif //AP_MAIN_HPP

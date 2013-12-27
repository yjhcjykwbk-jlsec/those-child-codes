class test95{
    public static void main(String[] a){
	System.out.println(new Test().start());
    }
}

class Test {

    Test test;
    int[] i;

    public int start(){

	i = new int[10];

	test = ((new Test()).next()).next();
	
	return 0;
    }

    public Test next() {
	
	return test;
    }
}

class test3 extends test6
{
}
class test4 extends test3
{
}
class test5 extends test4
{
}
class test6 extends test5
{}
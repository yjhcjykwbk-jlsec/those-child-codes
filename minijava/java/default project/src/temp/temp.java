package temp;

public class temp{
	public boolean isReg=true;
	public int val;
	public void setReg(int reg)
	{
		this.val=reg;
		isReg=true;
	}
	public void setCons(int constant)
	{
		this.val=constant;
		isReg=false;
	}
	public String toString()
	{
		return (""+val);
	}
}

package Schedule;

import java.text.SimpleDateFormat;
import java.util.Date;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

import ConvenienceStore.CU;

public class CUUpDateJob implements Job{
	public void execute(JobExecutionContext jec) throws JobExecutionException {
		System.out.println("CU Update Execute : "+ new SimpleDateFormat("yyyy-MM-dd-HH:mm:ss").format(new Date()));
		CU.getCU().cuUpdate();
		System.out.println("CU Update Execute END : "+ new SimpleDateFormat("yyyy-MM-dd-HH:mm:ss").format(new Date()));
	}
}

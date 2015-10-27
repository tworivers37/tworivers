package Schedule;

import java.text.SimpleDateFormat;
import java.util.Date;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

import ConvenienceStore.GS;

public class GS25UpDateJob implements Job{

	@Override
	public void execute(JobExecutionContext arg0) throws JobExecutionException {
		System.out.println("GS25 Update Execute : "+ new SimpleDateFormat("yyyy-MM-dd-HH:mm:ss").format(new Date()));
		GS.getGS().gsUpdate();
		System.out.println("GS25 Update Execute END : "+ new SimpleDateFormat("yyyy-MM-dd-HH:mm:ss").format(new Date()));
	}
	
}

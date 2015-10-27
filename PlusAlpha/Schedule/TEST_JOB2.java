package Schedule;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

public class TEST_JOB2 implements Job{

	public void execute(JobExecutionContext arg0) throws JobExecutionException {
		System.out.println("TEST_JOB2");		
	}

}

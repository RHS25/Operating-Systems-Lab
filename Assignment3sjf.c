#include <stdio.h>
  
int main() 
{
      int arrival_time[10], burst_time[10], temp[10];
      int i, smallest, count = 0, time, limit;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      printf("\n Enter the Total Number of Processes:");
      scanf("%d", &limit); 
      printf("\n Enter Details of %d Processes", limit);
      for(i = 0; i < limit; i++)
      {
            
	    printf("\n Enter Arrival Time:");
            scanf("%d", &arrival_time[i]);
            printf("\n Enter Burst Time:");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      }
      burst_time[9] = 9999;
      printf("\n Process ID\t\twait_time\t\t turnaround_time");  
      
      for(time = 0; count != limit; time++)
      {
            
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
		             
		if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
	    
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
		  printf("\n %d \t\t%f\t\t %f", smallest,wait_time, turnaround_time);
            }
      }
      average_waiting_time = wait_time / limit; 
      average_turnaround_time = turnaround_time / limit;
      printf("\n Average Waiting Time:%lf", average_waiting_time);
      printf("\n Average Turnaround Time:%lf", average_turnaround_time);
      return 0;
}

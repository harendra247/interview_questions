select concat(customer_name,
   , case when count(case when status <> 'CREATED' then 1 end) = 0 then 'AWAITING SUBMISSION'
          when count(case when status <> 'SUBMITTED' then 1 end) = 0 then 'AWAITING PROGRESS'
          when count(case when status <> 'DELIVERED' then 1 end) > 0 then 'IN PROGRESS'
          when count(case when status <> 'DELIVERED' then 1 end) = 0 then 'COMPLETED'
     end)
from customer_order
group by customer_name
ORDER BY customer_name ASC;

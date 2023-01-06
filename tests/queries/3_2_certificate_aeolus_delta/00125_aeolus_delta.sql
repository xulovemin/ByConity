SET output_format_write_statistics = 0;
SELECT (p_date) AS _1499526, (case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end) AS _1503054, (case   when (split(department,'-')[4])='' then '-'   else split(department,'-')[4]   end) AS _1700006412714, (case when department like '%投后巡检组%' then  split(department,'-')[6] else  concat(substring(department,length(department)-3,1),'组') end) AS _1700007275599, (hour) AS _1499527, (staff_id) AS _1499533, (name) AS _1499534, (case when department like '%成都%' then '成都' when department like '%西安%' then '西安'  when department like '%合肥%' then '合肥' when department like '%太原%'  then '太原' when department like '%郑州%'  then '郑州' when department like '%BPO%'  then 'BPO' else '其他地区' end) AS _1700001000493, (sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1535251, (sum(manual_pass_cnt)/sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1700003698738, (sum(manual_audit_time_total)/sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1499544, (sum(manual_delay_time_total)/sum(valid_audit_cnt+null_valid_audit_cnt)/60) AS _1700003698790 FROM `aeolus_data_db_aeolus_delta_202002`.`aeolus_data_table_29307_prod` SAMPLE 1.0 WHERE (((((p_date >= '2021-08-06') AND (p_date <= '2021-08-06')) AND ((case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end) = ('游戏视频')) AND ((case when department like '%投后巡检组%' then  split(department,'-')[6] else  concat(substring(department,length(department)-3,1),'组') end) = ('D组')) AND ((case when department like '%成都%' then '成都' when department like '%西安%' then '西安'  when department like '%合肥%' then '合肥' when department like '%太原%'  then '太原' when department like '%郑州%'  then '郑州' when department like '%BPO%'  then 'BPO' else '其他地区' end) = ('合肥'))))) GROUP BY p_date, case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end, case   when (split(department,'-')[4])='' then '-'   else split(department,'-')[4]   end, case when department like '%投后巡检组%' then  split(department,'-')[6] else  concat(substring(department,length(department)-3,1),'组') end, hour, staff_id, name, case when department like '%成都%' then '成都' when department like '%西安%' then '西安'  when department like '%合肥%' then '合肥' when department like '%太原%'  then '太原' when department like '%郑州%'  then '郑州' when department like '%BPO%'  then 'BPO' else '其他地区' end ORDER BY _1499526 ASC LIMIT 1000 FORMAT JSONCompact  SETTINGS fallback_to_stale_replicas_for_distributed_queries=0,max_replica_delay_for_distributed_queries = 1
SET output_format_write_statistics = 0;
SELECT (p_date) AS _1499526, (staff_id) AS _1499533, (name) AS _1499534, (department) AS _1499536, (first_item) AS _1503043, (case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end) AS _1503054, (sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1535251, (sum(manual_pass_cnt)/sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1700003698738, (sum(manual_audit_time_total)/sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1499544 FROM `aeolus_data_db_aeolus_delta_202002`.`aeolus_data_table_29307_prod` SAMPLE 1.0 WHERE (((((p_date >= '2021-08-02') AND (p_date <= '2021-08-02')) AND ((case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end) IN (('企业号 - POI认领（旧）'), ('企业号-POI认领（旧）'))) AND ((case when department like '%成都%' then '成都' when department like '%太原%' then '太原' end) = ('太原'))))) GROUP BY p_date, staff_id, name, department, first_item, case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end ORDER BY _1499526 ASC LIMIT 1000 FORMAT JSONCompact  SETTINGS fallback_to_stale_replicas_for_distributed_queries=0,max_replica_delay_for_distributed_queries = 1
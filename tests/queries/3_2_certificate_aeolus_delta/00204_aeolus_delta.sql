SET output_format_write_statistics = 0;
SELECT (name) AS _1499534, (staff_id) AS _1499533, (first_item) AS _1503043, (case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end) AS _1503054, (sum(valid_audit_cnt)) AS _1499541, (sum(null_valid_audit_cnt)) AS _1499542, (sum(non_valid_audit_cnt)) AS _1499543, (sum(manual_audit_time_total)/sum(valid_audit_cnt+null_valid_audit_cnt)) AS _1499544 FROM `aeolus_data_db_aeolus_delta_202002`.`aeolus_data_table_29307_prod` SAMPLE 1.0 WHERE (((((p_date >= '2021-07-31') AND (p_date <= '2021-07-31')) AND ((active) = (1)) AND ((staff_id) = (2797025)) AND ((toString(staff_id)) = ('2797025'))))) GROUP BY name, staff_id, first_item, case when object_category=1000115 then '鲁班落地页审核'   when object_category=1000056 then 'dsp抖音广告（新）'    when object_category=1000057 then 'dsp创建广告（新）' else    second_item end HAVING ((((sum(valid_audit_cnt+null_valid_audit_cnt+non_valid_audit_cnt)) > (0)))) ORDER BY _1499534 DESC LIMIT 1000 FORMAT JSONCompact  SETTINGS fallback_to_stale_replicas_for_distributed_queries=0,max_replica_delay_for_distributed_queries = 1
import requests
import json

url = "https://solved.ac/api/v3/tag/list"
header = {
    'Content-Type': 'application/json'
}

json_data = json.loads(requests.get(url, headers=header).text)
print(f"Found {json_data['count']} Tags")
tag_items = json_data['items']

problem_tags = []
for tag in tag_items:
    problem_tag = ['', ''] # English, Korean
    for item in tag['displayNames']:
        if item['language'] == 'ko':
            problem_tag[1] = item['name']
        if item['language'] == 'en':
            problem_tag[0] = item['name']
    problem_tags.append(problem_tag)

# Save to markdown (tags.md)
markdown_file = open('tags.md', 'w')
markdown_file.write('# Problem Tags\n')
markdown_file.write('\n')
for en, ko in problem_tags: markdown_file.write(f" - {en} ({ko})\n")
markdown_file.close()